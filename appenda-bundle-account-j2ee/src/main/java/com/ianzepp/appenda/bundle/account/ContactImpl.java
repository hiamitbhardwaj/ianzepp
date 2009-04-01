package com.ianzepp.appenda.bundle.account;

import java.io.Serializable;
import java.util.Date;
import java.util.List;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.ManyToMany;
import javax.persistence.Table;


@Entity
@Table(name = "contacts")
public class ContactImpl implements Contact, Serializable {
	private static final long serialVersionUID = -3652101379728477994L;
	private List<Account> accounts;
	private List<Address> addresses;
	private Date created;
	private Date deleted;
	private String id;
	private String name;
	private List<Phone> phones;
	private Date updated;

	@ManyToMany(targetEntity = AccountImpl.class, mappedBy = "account_id")
	public List<Account> getAccounts() {
		return accounts;
	}

	@ManyToMany(targetEntity = AddressImpl.class, mappedBy = "address_id")
	public List<Address> getAddresses() {
		return addresses;
	}

	@Column(name = "created_at")
	public Date getCreated() {
		return created;
	}

	@Column(name = "deleted_at")
	public Date getDeleted() {
		return deleted;
	}

	@EmbeddedId
	@Column(name = "contact_id")
	public String getId() {
		return id;
	}

	@Column(name = "name")
	public String getName() {
		return name;
	}

	@ManyToMany(targetEntity = PhoneImpl.class, mappedBy = "phone_id")
	public List<Phone> getPhones() {
		return phones;
	}

	@Column(name = "updated_at")
	public Date getUpdated() {
		return updated;
	}

	public void setAccounts(List<Account> accounts) {
		this.accounts = accounts;
	}

	public void setAddresses(List<Address> addresses) {
		this.addresses = addresses;
	}

	public void setCreated(Date created) {
		this.created = created;
	}

	public void setDeleted(Date deleted) {
		this.deleted = deleted;
	}

	public void setId(String id) {
		this.id = id;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setPhones(List<Phone> phones) {
		this.phones = phones;
	}

	public void setUpdated(Date updated) {
		this.updated = updated;
	}
}
