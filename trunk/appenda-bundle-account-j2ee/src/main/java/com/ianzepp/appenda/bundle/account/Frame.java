package com.ianzepp.appenda.bundle.account;

import java.io.InputStream;
import java.util.Set;

public interface Frame<Model> {
	public InputStream getAttachment(String name);

	public Set<String> getAttachmentNames();

	public Exception getFault();

	public String getHeader(String name);

	public Set<String> getHeaderNames();

	public Model getPayload();

	public void setAttachment(String name, InputStream inputStream);

	public void setFault(Exception exception);

	public void setHeader(String name, String value);

	public void setPayload(Model model);
}
