package com.ianzepp.appenda.bundle.account;

import java.util.Date;
import java.util.List;

public interface FindContactService extends Service {
	public Contact findContactById(String id);

	public Contact findContactByName(String name);

	public List<Contact> findContactListByAccountId(String accountId);

	public List<Contact> findContactListByCreatedDate(Date minimum, Date maximum);

	public List<Contact> findContactListByDeletedDate(Date minimum, Date maximum);
}
