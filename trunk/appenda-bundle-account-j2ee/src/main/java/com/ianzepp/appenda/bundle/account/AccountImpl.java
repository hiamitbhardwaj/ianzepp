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
@Table(name = "accounts")
public class AccountImpl implements Account, Serializable {
	private static final long serialVersionUID = -5171668494432969588L;
	private List<Address> addresses;
	private List<Contact> contacts;
	private Date created;
	private Date deleted;
	private String id;
	private String name;
	private List<Phone> phones;
	private Date updated;

	@ManyToMany(targetEntity = AddressImpl.class, mappedBy = "address_id")
	public List<Address> getAddresses() {
		return addresses;
	}

	@ManyToMany(targetEntity = ContactImpl.class, mappedBy = "contact_id")
	public List<Contact> getContacts() {
		return contacts;
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
	@Column(name = "account_id")
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

	public void setAddresses(List<Address> addresses) {
		this.addresses = addresses;
	}

	public void setContacts(List<Contact> contacts) {
		this.contacts = contacts;
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
