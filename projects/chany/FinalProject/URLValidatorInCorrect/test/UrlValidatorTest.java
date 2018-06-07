
// ******************************************************************
// Group: Yau Chan (chany), Dat Pham (phamdat), Tanya Haddad (haddadt)
// Due Date: June 11th, 2018
// CS362: Final Project Part B
// ******************************************************************


import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
/*   public void testManualTest()
   {
//You can use this function to implement your manual testing
	   String[] urlArr = {	"http://www.google.com",
			   				"http://www.google.com/",
			   				"http://www.google.abc",
			   				"https://www.google.com",
			   				"http://www.google.com/",
			   				//"abc://www.google.com/",
			   				"www.google.net/",
			   				"255.255.255.255",
			   				//"go.com",
			   				//"h3t://255.com:0",
			   				//"ftp://255.com:80",
			   				"http://www.microsoft.com/"};
	   int urlTotal = urlArr.length;
	   testIsValid(urlArr, UrlValidator.ALLOW_ALL_SCHEMES, urlTotal);
	   //assertTrue(urlVal.isValid("http://www.google.com"));
   }*/
   
   

   //You need to create more test cases for your Partitions if you need to 
   
   //public void testIsValid(Object[] testObjects, long allowAllSchemes, int urlTotal)
   public void testIsValid(String[] url, long allowAllSchemes, int urlTotal)
   {
	   // Function for programming based testing
	   UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
	   boolean val;
	   int err_cnt = 0;
	   //StringBuilder testBuffer = new StringBuilder();
	   for(int i = 0; i < urlTotal; i++) { 
		   val = urlVal.isValid(url[i]);
		   if(val)
			   System.out.println("Pass: "+url[i]);
		   else {
			   System.out.println("Fail: "+url[i]);
			   err_cnt++;
		   }
	   }
	   
	   //assertEquals("Failure", 0, err_cnt);
	   System.out.println("Total failed: "+err_cnt);
   }
   
	// Testing URL Scheme Authority partition
	
	public void testUrlSchemeAuthority() {

		System.out.println("\nRunning programming based testing for scheme+authority...");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

		String url;
		Boolean urlValid;
		for (ResultPair i : testUrlScheme) {

			for (ResultPair j : testUrlAuthority) {
				url = i.item + j.item;
				urlValid = urlVal.isValid(url);
				if ((i.valid && j.valid && urlValid) || ((!i.valid || !j.valid) && !urlValid)) {
					// Tests pass if both components are valid and the url is
					// valid
					// OR
					// if either of the components are invalid and the url is
					// invalid
					System.out.println("Passed: URL -> <" + url + ">... Expected: " + (i.valid && j.valid)
							+ ". Actual: " + urlValid);
				} else {
					System.out.println("Failed: URL -> <" + url + ">. Expected: " + (i.valid && j.valid) + ". Actual: "
							+ urlValid);
				}
			}
		}
	}
	
	
	// Testing URL Ports partition
	// Loops though different different ports with the rest of the url being valid
	
		public void testUrlPort() {

			System.out.println("\nRunning programming based testing for port...");
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

			String baseUrl = "http://www.google.com";
			String url;
			Boolean urlValid;

			for (ResultPair j : testUrlPort) {
				url = baseUrl + j.item;
				urlValid = urlVal.isValid(url);
				if ((j.valid && urlValid) || (!j.valid && !urlValid)) {
					// Tests pass if port is valid and the url is valid
					// OR
					// if port is invalid and the url is invalid
					System.out.println("Passed: URL -> <" + url + ">... Expected: " + j.valid + ". Actual: " + urlValid);
				} else {
					System.out.println("Failed: URL -> <" + url + ">... Expected: " + j.valid + ". Actual: " + urlValid);
				}
			}
		}

	
	// Testing URL Path partition
	// Loop though different paths with the rest of the url being valid
	
		public void testUrlPath() {

			System.out.println("\nRunning programming based testing for path...");
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

			String baseUrl = "http://www.google.com:80";
			String url;
			Boolean urlValid;

			for (ResultPair j : testUrlPath) {
				url = baseUrl + j.item;
				urlValid = urlVal.isValid(url);
				if ((j.valid && urlValid) || (!j.valid && !urlValid)) {
					// Tests pass if port is valid and the url is valid
					// OR
					// if port is invalid and the url is invalid
					System.out.println("Passed: URL -> <" + url + ">... Expected: " + j.valid + ". Actual: " + urlValid);
				} else {
					System.out.println("Failed: URL -> <" + url + ">... Expected: " + j.valid + ". Actual: " + urlValid);
				}
			}
		}

	// Testing URL queries partition
	// Loop though different queries with the rest of the url being valid
	
		public void testUrlQuery() {

			System.out.println("\nRunning programming based testing for query...");
			UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

			String baseUrl = "http://www.google.com:80/blah";
			String url;
			Boolean urlValid;

			for (ResultPair j : testUrlQuery) {
				url = baseUrl + j.item;
				urlValid = urlVal.isValid(url);
				if ((j.valid && urlValid) || (!j.valid && !urlValid)) {
					// Tests pass if port is valid and the url is valid
					// OR
					// if port is invalid and the url is invalid
					System.out.println("Passed: URL -> <" + url + ">... Expected: " + j.valid + ". Actual: " + urlValid);
				} else {
					System.out.println("Failed: URL -> <" + url + ">... Expected: " + j.valid + ". Actual: " + urlValid);
				}
			}
		}

	
	// Input data for partition testing
	
		ResultPair[] testUrlScheme = { new ResultPair("http://", true), new ResultPair("https://", true),
				new ResultPair("ftp://", true), new ResultPair("blah://", true), new ResultPair("://", false),
				new ResultPair("/", false), new ResultPair(":", false), new ResultPair("123", false),
				new ResultPair("!!", false), new ResultPair("http:", false), };

		ResultPair[] testUrlAuthority = { new ResultPair("www.google.com", true), new ResultPair("google.com", true),
				new ResultPair("192.168.0.0", true), new ResultPair("1000.1000.1000.1000", false), new ResultPair("1.1.1.256", false),
				new ResultPair("1000.10.10.10", false), new ResultPair("....", false), new ResultPair("abc", false),
				new ResultPair("123", false), new ResultPair(".a.b.a.", false) };

		ResultPair[] testUrlPort = { new ResultPair("", true), new ResultPair(":80", true), new ResultPair(":8080", true),
				new ResultPair(":80808", false), new ResultPair(":808080", false), new ResultPair(":8a", false),
				new ResultPair(":8A", false), new ResultPair(":88A8", false), new ResultPair(":8AAAAA", false),
				new ResultPair(":!@#", false), new ResultPair(":-100", false) };

		ResultPair[] testUrlPath = { new ResultPair("", true), new ResultPair("/blah", true), new ResultPair("/.", true),
				new ResultPair("/..", false), new ResultPair("/...", false), new ResultPair("/?", true),
				new ResultPair("/??", true), new ResultPair("/blah/foo", true), new ResultPair("/blah/foo/bar", true) };

		ResultPair[] testUrlQuery = { new ResultPair("", true), new ResultPair("?key==value", true),
				new ResultPair("?key===value", true), new ResultPair("?key=?value", true),
				new ResultPair("?key=??value", true) };
	
   //public static void main(String[] argv) {

	  //UrlValidatorTest fct = new UrlValidatorTest("url test");
	  //fct.testUrlSchemeAuthority();
	  //fct.testUrlPort();
	  //fct.testUrlPath();
	  //fct.testUrlQuery();

   //}

}
   
}
