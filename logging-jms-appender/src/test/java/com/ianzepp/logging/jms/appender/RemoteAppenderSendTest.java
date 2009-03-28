package com.ianzepp.logging.jms.appender;

import org.apache.log4j.Appender;
import org.apache.log4j.Logger;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * 
 * TODO Type description
 * 
 * @author izepp
 */
public class RemoteAppenderSendTest {
	private static Logger LOG;

	/**
	 * 
	 * TODO Type description
	 * 
	 * @author izepp
	 */
	private class RemoteAppenderSendException extends Exception {
		private static final long serialVersionUID = 1L;
	}

	/**
	 * 
	 * TODO Method description for <code>newRemoteAppender()</code>
	 * 
	 * @return
	 */
	private static Appender newRemoteAppender() {
		String conversionPattern = "[%d{MMM dd HH:mm:ss}] %-5p (%F:%L) - %m%n";
		RemoteAppender remoteAppender = new RemoteAppender();
		remoteAppender.setBrokerUri("tcp://localhost:61616");
		remoteAppender.setQueueName("com.ianzepp.logging.events");
		remoteAppender.setLayout(new org.apache.log4j.PatternLayout(conversionPattern));
		return remoteAppender;
	}

	/**
	 * 
	 * TODO Method description for <code>newRemoteAppenderSendException()</code>
	 * 
	 * @return
	 */
	private Exception newRemoteAppenderSendException() {
		return new RemoteAppenderSendException();
	}

	/**
	 * 
	 * TODO Method description for <code>setUpBeforeClass()</code>
	 * 
	 */
	@BeforeClass
	public final static void setUpBeforeClass() {
		LOG = Logger.getLogger(RemoteAppenderSendTest.class);
		LOG.addAppender(newRemoteAppender());
	}

	/**
	 * 
	 * TODO Method description for <code>tearDownAfterClass()</code>
	 * 
	 */
	@AfterClass
	public final static void tearDownAfterClass() {
		LOG = null;
	}

	/**
	 * 
	 * TODO Method description for <code>testSend()</code>
	 * 
	 */
	@Test
	public final void testSend() {
		LOG.info("Sent from RemoteAppenderSendTest.testSend()");
	}

	/**
	 * 
	 * TODO Method description for <code>testSendWithException()</code>
	 * 
	 */
	@Test
	public final void testSendWithException() {
		LOG.info("Sent from RemoteAppenderSendTest.testSendWithException()", newRemoteAppenderSendException());
	}
}
