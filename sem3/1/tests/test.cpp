#define CATCH_CONFIG_MAIN
#include "../properties/properties.h"
#include "catch.hpp"

TEST_CASE("from properties") {
	SECTION("string nothtow case") {
		std::vector<std::string> t = {
			"t.1=3453234\nt.2=9\nt.3=0923",
			"t23.1=3453234\nt23.2gr342=9\nt23.tg343=04923\n",
			"t23.1=3453234\nt23.2gr342=9\nt23.tg343=04923\nhoppi"
		};
		std::vector<int> a = {3453234, 9, 923};
		std::vector<int> b = {3453234, 9, 4923};
		REQUIRE_NOTHROW(FromJavaProperties(t[0]) == a);
		REQUIRE_NOTHROW(FromJavaProperties(t[1]) == b);
		REQUIRE_NOTHROW(FromJavaProperties(t[2]) == b);

		char u[] = "t.1=3453234\nt.2=9\nt.3=0923";
		size_t p = 30;

		REQUIRE_NOTHROW(FromJavaProperties(u) == a);
		REQUIRE_NOTHROW(FromJavaProperties(u, p) == a);
	}
	SECTION("string throw case") {
		std::vector<std::string> t = {
			"t23.1=3453234\nt23.2gr342=9\nt23.tg343=0geg4923\n\n\n",
			"t23.1=3453234\nt43t.2gr342=9\nt34g.tg343=0geg4923",
			"t23.1=3453234\nt23.2=9\nt23.t=0,ch.",
			"t23.1=3453234\nt23.2=9\nt23.t=0,ch=",
		};
		
		REQUIRE_THROWS(FromJavaProperties(t[0]));
		REQUIRE_THROWS(FromJavaProperties(t[1]));
		REQUIRE_THROWS(FromJavaProperties(t[2]));
		REQUIRE_THROWS(FromJavaProperties(t[3]));
	}
	SECTION("char* nothrow case") {
		char t[] = "t.1=3453234\nt.2=9\nt.3=0923";
		REQUIRE_NOTHROW(FromJavaProperties((char*)t));
		char d[] = "t.1=3453234\nt.2=9\nt.3=0923\nckljas23fef";
		REQUIRE_NOTHROW(FromJavaProperties((char*)d));
	}
	SECTION("char* throw case") {
		char t[] = "t23.1=3453234\nt23.2gr342=9\nt23.tg343=0geg4923\n\n\n";
		REQUIRE_THROWS(FromJavaProperties((char*)t));
		char d[] = "t23.1=3453234\nt23.2=9\nt23.t=0,ch.";
		REQUIRE_THROWS(FromJavaProperties((char*)d));
	}
	SECTION("empty line") {
		char t;
		char* d = &t;
		REQUIRE_THROWS(FromJavaProperties(d));
		std::string a = "";
		REQUIRE_THROWS(FromJavaProperties(a));
		char c[] = "";
		REQUIRE_THROWS(FromJavaProperties(c, 20));
	}

}

TEST_CASE("to properties") {
	SECTION("arr") {
		std::string name = "uii";
		std::vector<int> arr = {1, 2, 3, 4, 5};
		std::string res = "uii.1=1\nuii.2=2\nuii.3=3\nuii.4=4\nuii.5=5\n";
		REQUIRE(ToJavaProperties(arr, name) == res);
	}

	SECTION("empty arr") {
		std::vector<int> empty;
		std::string name = "ku";
		REQUIRE(ToJavaProperties(empty, name) == "");
	}
}