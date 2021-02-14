#include<iostream>

typedef long long ll;

using namespace std;

ll prm= 101;

ll pow_a_b(ll a, ll b, ll mod)
{
	ll ans= 1;
	while(b)
	{
		if(b&1) ans= (ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans%mod;
}


int main()
{
    ll xa, ya, xb, yb, alfa= 3, ka, kb;
    cout<< "Enter chosen private key for A: ";
    cin>> xa;
    cout<< "Enter chosen private key for B: ";
    cin>> xb;

    ya= pow_a_b(alfa, xa, prm);
    yb= pow_a_b(alfa, xb, prm);

    cout<< "Public code for A: "<< ya<< '\n';
    cout<< "Public code for B: "<< yb<< '\n';

    ka= pow_a_b(yb, xa, prm);
    kb= pow_a_b(ya, xb, prm);

    cout<< "Secret key for A: "<< ka<< '\n';
    cout<< "Secret key for B: "<< kb<< '\n';
}