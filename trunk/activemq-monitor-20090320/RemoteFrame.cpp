/*
 * RemoteFrame.cpp
 *
 *  Created on: Mar 17, 2009
 *      Author: Ian Zepp
 */

#include "RemoteFrame.h"

RemoteFrame::RemoteFrame()
{
}

RemoteFrame::RemoteFrame(const QByteArray &frameData)
{
	// Split apart the headers from the body data
	QRegExp messageRegex("(.+\\n)\\n(.*)");
	QString message(frameData);
	int breakpoint = -1;

	if (!messageRegex.exactMatch(message))
	{
		throw QString("Failed to exactly match the incoming frame data: " + message);
	}

	// Extract the command value
	QString frameHeaders = messageRegex.cap(1);
	breakpoint = frameHeaders.indexOf('\n');

	// Save the command
	command = frameHeaders.left(breakpoint).trimmed();

	// Strip the command and the terminating newline from the headers
	frameHeaders.remove(0, breakpoint + 1);

	// Save the header property => value mappings
	while (frameHeaders.contains(QChar('\n')))
	{
		breakpoint = frameHeaders.indexOf('\n');
		QRegExp propertyRegex("(.+):(.+)");
		QString propertySet(frameHeaders.left(breakpoint).trimmed());
		frameHeaders.remove(0, breakpoint + 1);

		if (!propertyRegex.exactMatch(propertySet))
		{
			throw QString("Failed to match property item regex: " + propertySet);
		}

		QString property = propertyRegex.cap(1).trimmed();
		QString value = propertyRegex.cap(2).trimmed();

		// Save to the object headers hash
		headers.insert(property, value);
	}

	// Save the body data
	data = messageRegex.cap(2).trimmed().toUtf8();
}

RemoteFrame::~RemoteFrame()
{
}

QByteArray RemoteFrame::toFrame(bool includeTerminator) const
{
	QByteArray frameData;
	frameData.append(command.toUtf8());
	frameData.append('\n');

	QHashIterator<QString, QString> iterator(headers);

	while (iterator.hasNext())
	{
		iterator.next();

		frameData.append(iterator.key());
		frameData.append(": ");
		frameData.append(iterator.value());
		frameData.append('\n');
	}

	frameData.append('\n');
	frameData.append(data);

	if (includeTerminator)
	{
		frameData.append('\0');
		frameData.append('\n');
	}

	return frameData;
}

QString RemoteFrame::toNode(const QString &xpath)
{
	// Cached?
	if (cache.contains(xpath))
	{
		return cache.value(xpath);
	}

	QBuffer sourceBuffer;
	QBuffer targetBuffer;

	sourceBuffer.setData(getData());
	sourceBuffer.open(QIODevice::ReadOnly);
	targetBuffer.open(QIODevice::ReadWrite);

	QXmlQuery xmlQuery;
	xmlQuery.bindVariable("sourceBuffer", &sourceBuffer);
	xmlQuery.setQuery("doc($sourceBuffer)" + xpath);

	QXmlSerializer xmlSerializer(xmlQuery, &targetBuffer);
	xmlQuery.evaluateTo(&xmlSerializer);

	// Save to the cache
	QString nodeData(targetBuffer.buffer());
	cache.insert(xpath, nodeData);
	return nodeData;
}

QString RemoteFrame::toNodeText(const QString &xpath)
{
	QRegExp xmlMatcher("<.+>(.+)</.+>");
	xmlMatcher.indexIn(toNode(xpath));
	return xmlMatcher.cap(1);
}

QString RemoteFrame::getRootName()
{
	QRegExp xmlMatcher("<(.+)>.+");
	xmlMatcher.indexIn(toNode("/"));
	return xmlMatcher.cap(1);
}
