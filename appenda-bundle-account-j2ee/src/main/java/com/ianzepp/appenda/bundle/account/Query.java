package com.ianzepp.appenda.bundle.account;

public interface Query<Frame> extends Model {
	public Frame getFrame();

	public Integer getLimit();

	public Integer getOffset();

	public void setFrame(Frame frame);

	public void setLimit(Integer limit);

	public void setOffset(Integer offset);
}
