package com.ianzepp.appenda.bundle.account;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;


@Entity
@Table(name = "addresses")
public class AddressImpl implements Address, Serializable {
	private static final long serialVersionUID = 2725345560944573165L;
	private String attention;
	private String city;
	private String company;
	private String country;
	private String id;
	private String postalCode;
	private String province;
	private String street1;
	private String street2;
	private String street3;

	@Column(name = "attention")
	public String getAttention() {
		return attention;
	}

	@Column(name = "city")
	public String getCity() {
		return city;
	}

	@Column(name = "company")
	public String getCompany() {
		return company;
	}

	@Column(name = "country")
	public String getCountry() {
		return country;
	}

	@EmbeddedId
	@Column(name = "address_id")
	public String getId() {
		return id;
	}

	@Column(name = "postal_code")
	public String getPostalCode() {
		return postalCode;
	}

	@Column(name = "province")
	public String getProvince() {
		return province;
	}

	@Column(name = "street_1")
	public String getStreet1() {
		return street1;
	}

	@Column(name = "street_2")
	public String getStreet2() {
		return street2;
	}

	@Column(name = "street_3")
	public String getStreet3() {
		return street3;
	}

	@Transient
	public String[] getStreets() {
		return new String[] { getStreet1(), getStreet2(), getStreet3() };
	}

	public void setAttention(String attention) {
		this.attention = attention;
	}

	public void setCity(String city) {
		this.city = city;
	}

	public void setCompany(String company) {
		this.company = company;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	public void setId(String id) {
		this.id = id;
	}

	public void setPostalCode(String postalCode) {
		this.postalCode = postalCode;
	}

	public void setProvince(String province) {
		this.province = province;
	}

	public void setStreet1(String street1) {
		this.street1 = street1;
	}

	public void setStreet2(String street2) {
		this.street2 = street2;
	}

	public void setStreet3(String street3) {
		this.street3 = street3;
	}
}
