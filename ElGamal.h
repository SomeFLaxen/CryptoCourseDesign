﻿#pragma once
#include <NTL/ZZ.h>
#include <fstream>
using namespace std;
#include <ctime>

using namespace NTL;

//生成大素数p、本原元aa和私钥a
void createkeys(ZZ& p, ZZ& aa, ZZ& bb, ZZ& a)
{

	ZZ p_, j, q;
	bool aa_flag = false;

	do {
		SetSeed(to_ZZ((long)time(NULL)) * to_ZZ((long)time(NULL)));
		GenGermainPrime(p_, 20);
		p = 2 * p_ + 1;
	} while (MillerWitness(p, p_) == 1);

	do {

		SetSeed(to_ZZ((long)time(NULL)) * to_ZZ((long)time(NULL)));
		aa = RandomBnd(p);

		for (aa_flag = true, q = 2; q < p - 1; q = NextPrime(q + 1))
		{
			ZZ gcd = GCD(p - 1, q);
			if (GCD(p - 1, q) == 1)
				continue;
			else
				if (PowerMod(aa, (p - 1) / gcd, p) == 1)
				{
					aa_flag = false;
					break;
				}
		}
	} while (aa_flag == false);

	do {

		SetSeed(to_ZZ((long)time(NULL)) * to_ZZ((long)time(NULL)));
		a = RandomBnd(p - 1);
	} while (a == 0 || GCD(p - 1, a) != 1);


	bb = PowerMod(aa, a, p);

}


void Alice(ZZ & x, ZZ & r, ZZ & o, ZZ & p, ZZ & aa, ZZ & a)
{
	cout << "_Alice_\n";

	cout << "Please input news=";
	cin >> x;

	ZZ k, k_;
	do {

		SetSeed(to_ZZ((long)time(NULL)) * to_ZZ((long)time(NULL)));
		k = RandomBnd(p - 1);
	} while (k == 0 || GCD(p - 1, k) != 1);

	r = PowerMod(aa, k, p);
	ZZ b1, ZZ, b2;
	XGCD(b1, k_, b2, k, p - 1);
	o = (x - a * r) * k_ % (p - 1);

	cout << "result:";
	cout << "\nk:" << k;
	cout << "\nr:" << r;
	cout << "\no:" << o;

	cout << "\n\n";
}

void Oscar(ZZ & x, ZZ & r, ZZ & o)
{
	ZZ xx, rr, oo;
	cout << "_Oscar_\n";
	cout << "chang News or Signature(press 0 to give up)\n";
	cout << "News=";
	cin >> xx;
	cout << "Signature_r=";
	cin >> rr;
	cout << "Signature_o=";
	cin >> oo;

	if (xx != 0)
		x = xx;
	if (rr != 0)
		r = rr;
	if (oo != 0)
		o = oo;

	cout << "\n";
}

//bob判断两次签名是否相同
void Bob(ZZ & x, ZZ & r, ZZ & o, ZZ & p, ZZ & aa, ZZ & bb)
{
	cout << "_Bob_\n";
	ZZ ver1, ver2;
	ver1 = PowerMod(bb, r, p) * PowerMod(r, o, p);
	ver1 = ver1 % p;
	ver2 = PowerMod(aa, x, p);
	if (ver1 == ver2)
		cout << "SUCCESS";
	else
		cout << "FAILURE";

	cout << "\n";
}

/*void main()
{
	int pause;
	ZZ p, aa, bb, a, x, r, o;
	createkeys(p, aa, bb, a);
	Alice(x, r, o, p, aa, a);
	Oscar(x, r, o);
	Bob(x, r, o, p, aa, bb);


	cin >> pause;
}*/
