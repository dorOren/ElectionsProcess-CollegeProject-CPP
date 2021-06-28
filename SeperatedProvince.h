#pragma once
#include "Province.h"

namespace elections {
	class SeperatedProvince :virtual public province {

	public:
		SeperatedProvince (string _name = "\0", int _senNum = 0);                //constructor
		virtual ~SeperatedProvince(){}                                          //destructor
		SeperatedProvince (const SeperatedProvince& other) { *this = other; }  //copy constructor

		//other methods
		virtual void      chooseElectors  ()const override;
		virtual const int returnType      ()const override;

		//operators
		virtual SeperatedProvince const& operator= (SeperatedProvince const& other);
		virtual ostream&                 Print     (ostream& os) const;

		//save & load
		void save (ostream& out)const;
		void load (istream& in);

	};
}
