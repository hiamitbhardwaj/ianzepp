package com.ianzepp.appenda.bundle.account;

import java.util.Date;
import java.util.List;

public interface FindAccountService extends Service {
	public Account findAccountById(String id);

	public Account findAccountByName(String name);

	public List<Account> findAccountListByContactId(String contactId);

	public List<Account> findAccountListByCreatedDate(Date minimum, Date maximum);

	public List<Account> findAccountListByDeletedDate(Date minimum, Date maximum);
}
