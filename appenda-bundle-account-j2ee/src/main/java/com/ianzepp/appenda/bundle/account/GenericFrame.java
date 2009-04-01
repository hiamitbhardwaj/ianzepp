package com.ianzepp.appenda.bundle.account;

import java.io.InputStream;
import java.util.HashMap;
import java.util.Set;


public class GenericFrame<Model> implements Frame<Model> {
	public static final String CorrelationIdHeader = "correlation-id";
	public static final String DestinationHeader = "destination";
	public static final String IdHeader = "id";
	public static final String MessageIdHeader = "message-id";
	public static final String ResponseDestinationHeader = "reply-to";

	private final HashMap<String, InputStream> attachments = new HashMap<String, InputStream>();
	private Exception fault;
	private final HashMap<String, String> headers = new HashMap<String, String>();
	private Model payload;

	public InputStream getAttachment(String name) {
		return attachments.get(name);
	}

	public Set<String> getAttachmentNames() {
		return attachments.keySet();
	}

	public String getCorrelationId() {
		return getHeader(CorrelationIdHeader);
	}

	public String getDestination() {
		return getHeader(DestinationHeader);
	}

	public Exception getFault() {
		return fault;
	}

	public String getHeader(String name) {
		return headers.get(name);
	}

	public Set<String> getHeaderNames() {
		return headers.keySet();
	}

	public String getId() {
		return getHeader(IdHeader);
	}

	public String getMessageId() {
		return getHeader(MessageIdHeader);
	}

	public Model getPayload() {
		return payload;
	}

	public String getResponseDestination() {
		return getHeader(ResponseDestinationHeader);
	}

	public void setAttachment(String name, InputStream inputStream) {
		attachments.put(name, inputStream);
	}

	public void setCorrelationId(String correlationId) {
		setHeader(CorrelationIdHeader, correlationId);
	}

	public void setDestination(String destination) {
		setHeader(DestinationHeader, destination);
	}

	public void setFault(Exception exception) {
		fault = exception;
	}

	public void setHeader(String name, String value) {
		headers.put(name, value);
	}

	public void setId(String destination) {
		setHeader(IdHeader, destination);
	}

	public void setMessageId(String messageId) {
		setHeader(MessageIdHeader, messageId);
	}

	public void setPayload(Model model) {
		payload = model;
	}

	public void setResponseDestination(String responseDestination) {
		setHeader(ResponseDestinationHeader, responseDestination);
	}

}
