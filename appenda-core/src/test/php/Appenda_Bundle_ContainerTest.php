<?php

/**
 * The MIT License
 * 
 * Copyright (c) 2009 Ian Zepp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * @author Ian Zepp
 * @package 
 */

require_once "PHPUnit/Framework.php";
require_once "Appenda/Loader.php";

/** Tweak the include path */
set_include_path (get_include_path () . PATH_SEPARATOR . 'src/test/resources');
set_include_path (get_include_path () . PATH_SEPARATOR . 'src/main/resources');

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Bundle_ContainerTest extends PHPUnit_Framework_TestCase {
	/**
	 *
	 * @var Appenda_Bundle_BeanContainer
	 */
	private $instance;

	/**
	 *
	 * @return void
	 */
	public function setUp () {
		$this->instance = new Appenda_Bundle_Container ();
	}

	/**
	 *
	 * @return void
	 */
	public function tearDown () {
		$this->instance = null;
	}

	private function doProcessConfig () {
		$this->instance->processConfig ("Appenda/Core/BeanContainerTest.xml");
		$this->instance->processConfig ("Appenda/Service/Session/BeanConfiguration.xml");
	}

	private function doFindBean ($beanName) {
		return $this->instance->findBean ($beanName);
	}

	/**
	 * @expectedException
	 */
	public function testInstance () {
		$this->assertTrue ($this->instance instanceof Appenda_Bundle_BeanContainer);
	}

	/**
	 * @expectedException
	 */
	public function testProcessConfig () {
		$this->doProcessConfig ();
	}

	/**
	 * @expectedException
	 */
	public function testFindBean () {
		$this->doProcessConfig ();
		$this->assertNotNull ($this->doFindBean ("ConfigBean"));
	}

	/**
	 * @expectedException
	 */
	public function testBeanLoadedCorrectly () {
		$this->doProcessConfig ();
		$bean = $this->doFindBean ("ConfigBean")->getBeanInstance ();

		$this->assertEquals ("Appenda_Bundle_BeanContainerTest.ConfigBean.property01", $bean->property01);
		$this->assertEquals ("Appenda_Bundle_BeanContainerTest.ConfigBean.property02", $bean->property02);
		$this->assertEquals ("Appenda_Bundle_BeanContainerTest.ConfigBean.property03", $bean->property03);
		// throw new Exception (print_r ($this->instance->getBeans(), true));
	}
}

