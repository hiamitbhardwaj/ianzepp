package com.ianzepp.appenda.bundle.account;

public interface Phone extends Model {
	public Integer getCountryCode();

	public Integer getExtension();

	public String getId();

	public Integer getNumber();

	public void setCountryCode(Integer countryCode);

	public void setExtension(Integer extension);

	public void setId(String id);

	public void setNumber(Integer number);
}
