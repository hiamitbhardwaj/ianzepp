package com.ianzepp.appenda.bundle.account;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "phones")
public class Phone {
	private static final long serialVersionUID = -2571415896071574200L;
	private Integer countryCode;
	private Integer extension;
	private String id;
	private Integer number;

	@Column(name = "country_code")
	public Integer getCountryCode() {
		return countryCode;
	}

	@Column(name = "extension")
	public Integer getExtension() {
		return extension;
	}

	@Id
	@GeneratedValue
	@Column(name = "phone_id")
	public String getId() {
		return id;
	}

	@Column(name = "number")
	public Integer getNumber() {
		return number;
	}

	public void setCountryCode(Integer countryCode) {
		this.countryCode = countryCode;
	}

	public void setExtension(Integer extension) {
		this.extension = extension;
	}

	public void setId(String id) {
		this.id = id;
	}

	public void setNumber(Integer number) {
		this.number = number;
	}
}
