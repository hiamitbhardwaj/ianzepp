package com.ianzepp.appenda.bundle.account;

import java.util.Date;
import java.util.List;

public interface Account extends Model {
	public List<Address> getAddresses();

	public List<Contact> getContacts();

	public Date getCreated();

	public Date getDeleted();

	public String getId();

	public String getName();

	public List<Phone> getPhones();

	public Date getUpdated();

	public void setAddresses(List<Address> addresses);

	public void setContacts(List<Contact> contacts);

	public void setCreated(Date created);

	public void setDeleted(Date deleted);

	public void setId(String id);

	public void setName(String name);

	public void setPhones(List<Phone> phones);

	public void setUpdated(Date updated);
}
