#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ALERT invalid_argument
#define CATCH catch (exception& ex) { cout<< "Error: " << ex.what() << endl; valid=false; }
#define CATCH_EXIT catch (exception& ex) { cout<< "Error: " << ex.what() << endl; valid=false; return; }
#define CATCH_ALL  catch (...)
#define CHECK_BAD_ALLOC catch (bad_alloc& e) { (void)e; throw; }
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

enum DaysInMonth     //Shows amount of days in each month
{
	JANUARY = 31, FEBRUARY = 28, MARCH = 31, APRIL = 30, MAY = 31, JUNE = 30, JULY = 31,
	AUGUST = 31, SEPTEMBER = 30, OCTOBER = 31, NOVEMBER = 30, DECEMBER = 31
};

enum electionType { normal, simple };