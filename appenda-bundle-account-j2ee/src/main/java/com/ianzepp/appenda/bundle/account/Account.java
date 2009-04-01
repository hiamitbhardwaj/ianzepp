package com.ianzepp.appenda.bundle.account;

import java.util.Date;
import java.util.List;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.ManyToMany;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

@Entity
@Table(name = "accounts")
public class Account {
	private static final long serialVersionUID = -5171668494432969588L;
	private List<Address> addresses;
	private List<Contact> contacts;
	private Date created;
	private Date deleted;
	private String id;
	private String name;
	private List<Phone> phones;
	private Date updated;

	@ManyToMany(targetEntity = Address.class, mappedBy = "address_id")
	public List<Address> getAddresses() {
		return addresses;
	}

	@ManyToMany(targetEntity = Contact.class, mappedBy = "contact_id")
	public List<Contact> getContacts() {
		return contacts;
	}

	@Temporal(TemporalType.DATE)
	@Column(name = "created_at")
	public Date getCreated() {
		return created;
	}

	@Temporal(TemporalType.DATE)
	@Column(name = "deleted_at")
	public Date getDeleted() {
		return deleted;
	}

	@Id
	@GeneratedValue
	@Column(name = "account_id")
	public String getId() {
		return id;
	}

	@Column(name = "name")
	public String getName() {
		return name;
	}

	@ManyToMany(targetEntity = Phone.class, mappedBy = "phone_id")
	public List<Phone> getPhones() {
		return phones;
	}

	@Temporal(TemporalType.DATE)
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
