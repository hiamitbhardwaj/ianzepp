package com.ianzepp.appenda.bundle.account;

import java.util.List;
import java.util.Map;

public interface AccountDao {
	public Account find(String id);

	public void insert(Account account);

	public void update(Account account);

	public void delete(Account account);

	public List<Account> query(String queryString, final Map<String, Object> params);
}
