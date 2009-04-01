package com.ianzepp.appenda.bundle.account;


public abstract class GenericQuery<Frame, Result> implements Query<Frame> {
	private Frame frame;
	private Integer limit;
	private Integer offset;
	private Result result;

	public Frame getFrame() {
		return frame;
	}

	public Integer getLimit() {
		return limit;
	}

	public Integer getOffset() {
		return offset;
	}

	public Result getResult() {
		return result;
	}

	public void setFrame(Frame frame) {
		this.frame = frame;
	}

	public void setLimit(Integer limit) {
		this.limit = limit;
	}

	public void setOffset(Integer offset) {
		this.offset = offset;
	}

	public void setResult(Result result) {
		this.result = result;
	}
}
