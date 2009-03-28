package com.ianzepp.logging.jms.appender;

import org.apache.log4j.Logger;
import org.junit.After;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.fail;

public class RemoteAppenderTest
{
	private static final Logger LOG = Logger.getLogger (RemoteAppenderTest.class);
	private RemoteAppender remoteAppender;

	/**
	 * 
	 * TODO Method description for <code>newRemoteAppender()</code>
	 * 
	 * @return
	 */
	public RemoteAppender newRemoteAppender ()
	{
		return remoteAppender;
	}

	/**
	 * 
	 * TODO Method description for <code>setUp()</code>
	 * 
	 * @throws Exception
	 */
	@Before
	public void setUp () throws Exception
	{
		remoteAppender = new RemoteAppender ();
	}

	/**
	 * 
	 * TODO Method description for <code>tearDown()</code>
	 * 
	 * @throws Exception
	 */
	@After
	public void tearDown () throws Exception
	{
	}

	/**
	 * 
	 * TODO Method description for <code>testRequiresLayout()</code>
	 * 
	 */
	@Test
	public final void testRequiresLayout ()
	{
		assertFalse (newRemoteAppender ().requiresLayout ());
	}

	/**
	 * 
	 * TODO Method description for <code>testClose()</code>
	 * 
	 */
	@Test
	@Ignore
	public final void testClose ()
	{
	}

	/**
	 * 
	 * TODO Method description for <code>testGetDateFormat()</code>
	 * 
	 */
	@Test
	public final void testGetDateFormat ()
	{
		assertNotNull (newRemoteAppender ().getDateFormat ());
	}

	/**
	 * 
	 * TODO Method description for <code>testGetLocalHostName()</code>
	 * 
	 */
	@Test
	public final void testGetLocalHostName ()
	{
		assertNotNull (newRemoteAppender ().getLocalHostName ());
		assertFalse ("unknown.local".equals (newRemoteAppender ().getLocalHostName ()));
	}

	@Test
	public final void testSetLocalHostName ()
	{
		RemoteAppender remoteAppender = newRemoteAppender ();
		remoteAppender.setLocalHostName ("testSetLocalHostName");
		assertEquals ("testSetLocalHostName", remoteAppender.getLocalHostName ());
	}

	/**
	 * 
	 * TODO Method description for <code>testRemoteAppender()</code>
	 * 
	 */
	@Test
	public final void testRemoteAppender ()
	{
		assertNotNull (new RemoteAppender ());
	}

	/**
	 * 
	 * TODO Method description for <code>testAppendLoggingEvent()</code>
	 * 
	 */
	@Test
	@Ignore
	public final void testAppendLoggingEvent ()
	{
		fail ("Not yet implemented");
	}

	/**
	 * 
	 * TODO Method description for <code>testConvertToXml()</code>
	 * 
	 */
	@Test
	@Ignore
	public final void testConvertToXml ()
	{
		fail ("Not yet implemented");
	}

	/**
	 * 
	 * TODO Method description for <code>testBrokerUri()</code>
	 * 
	 */
	@Test
	public final void testBrokerUri ()
	{
		RemoteAppender remoteAppender = newRemoteAppender ();
		remoteAppender.setBrokerUri ("testBrokerUri");
		assertEquals ("testBrokerUri", remoteAppender.getBrokerUri ());
	}

	/**
	 * 
	 * TODO Method description for <code>testQueueName()</code>
	 * 
	 */
	@Test
	public final void testQueueName ()
	{
		RemoteAppender remoteAppender = newRemoteAppender ();
		remoteAppender.setBrokerUri ("testQueueName");
		assertEquals ("testQueueName", remoteAppender.getBrokerUri ());
	}

}
