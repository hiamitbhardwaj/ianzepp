package com.ianzepp.appenda.bundle.account;

public interface Address extends Model {
	public String getAttention();

	public String getCity();

	public String getCompany();

	public String getCountry();

	public String getId();

	public String getPostalCode();

	public String getProvince();

	public String getStreet1();

	public String getStreet2();

	public String getStreet3();

	public String[] getStreets();

	public void setAttention(String attention);

	public void setCity(String city);

	public void setCompany(String company);

	public void setCountry(String country);

	public void setId(String id);

	public void setPostalCode(String postalCode);

	public void setProvince(String province);

	public void setStreet1(String street1);

	public void setStreet2(String street2);

	public void setStreet3(String street3);

}
