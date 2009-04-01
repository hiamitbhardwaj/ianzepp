package com.ianzepp.appenda.bundle.account.jpa;

import java.util.List;
import java.util.Map;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import javax.sql.DataSource;

import com.ianzepp.appenda.bundle.account.Account;
import com.ianzepp.appenda.bundle.account.AccountDao;

public class AccountDaoJpa implements AccountDao {
	private EntityManager entityManager;

	@PersistenceContext
	public void setEntityManager(EntityManager entityManager) {
		this.entityManager = entityManager;
	}

	public void delete(Account account) {
	// TODO Auto-generated method stub

	}

	public Account find(String id) {
		StringBuilder stringBuilder = new StringBuilder();
		stringBuilder.append("SELECT DISTINCT account ");
		stringBuilder.append("FROM Account account ");
		stringBuilder.append("WHERE account.id = :id");

		Query query = entityManager.createNamedQuery(stringBuilder.toString());
		query.setParameter("id", id);
		return (Account) query.getSingleResult();
	}

	public void insert(Account account) {
	// TODO Auto-generated method stub

	}

	public void update(Account account) {
	// TODO Auto-generated method stub

	}

	public List<Account> query(String query, Map<String, Object> params) {
		return null;
	}
	
	public Account queryOne(String query, Map<String, Object> params) {
		return null;
	}
}
