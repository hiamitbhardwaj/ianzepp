/*
 * RemoteFrame.h
 *
 *  Created on: Mar 17, 2009
 *      Author: Ian Zepp
 */

#ifndef REMOTEFRAME_H_
#define REMOTEFRAME_H_

// System
#include <QtCore/QBuffer>
#include <QtCore/QByteArray>
#include <QtCore/QHash>
#include <QtCore/QRegExp>
#include <QtCore/QString>
#include <QtCore/QTime>

// System XML
#include <QtXmlPatterns/QXmlSerializer>
#include <QtXmlPatterns/QXmlQuery>

class RemoteFrame
{
public:
	RemoteFrame();
	RemoteFrame(const QByteArray &frameData);
	virtual ~RemoteFrame();

	inline const QString &getCommand() const
	{
		return command;
	}

	inline void setCommand(const QString &command)
	{
		this->command = command;
	}

	inline const QHash<QString, QString> &getHeaders() const
	{
		return headers;
	}

	inline QString getHeader(const QString &name) const
	{
		return headers.value(name);
	}

	inline void setHeader(const QString &name, const QString &property)
	{
		this->headers.insert(name, property);
	}

	inline const QByteArray &getData() const
	{
		return data;
	}

	inline void setData(const QByteArray & data)
	{
		this->data = QByteArray(data);
		this->cache.clear();
	}

public:
	QByteArray toFrame(bool includeTerminator = true) const;
	QString toNode(const QString &xpath);
	QString toNodeText(const QString &xpath);
	QString getRootName();

private:
	QString command;
	QHash<QString, QString> headers;
	QHash<QString, QString> cache;
	QByteArray data;
};

#endif /* REMOTEFRAME_H_ */
