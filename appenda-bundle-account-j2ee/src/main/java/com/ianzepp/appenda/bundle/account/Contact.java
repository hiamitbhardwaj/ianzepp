package com.ianzepp.appenda.bundle.account;

import java.util.Date;
import java.util.List;

public interface Contact extends Model {
	public List<Account> getAccounts();

	public List<Address> getAddresses();

	public Date getCreated();

	public Date getDeleted();

	public String getId();

	public String getName();

	public List<Phone> getPhones();

	public Date getUpdated();

	public void setAccounts(List<Account> accounts);

	public void setAddresses(List<Address> addresses);

	public void setCreated(Date created);

	public void setDeleted(Date deleted);

	public void setId(String id);

	public void setName(String name);

	public void setPhones(List<Phone> phones);

	public void setUpdated(Date updated);
}
