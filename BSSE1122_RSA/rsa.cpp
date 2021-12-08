#include<iostream>
#include<vector>

#define MAX_SIZE 100
#define debug(x) cout<< #x<< ": "<< x<< '\n'

typedef long long ll;

using namespace std;

const ll p= 61;
const ll q= 37;
ll fin, n, e=2, k=2, d;
double dp;

string msg, de_msg= "";
vector<ll> en_msg;

template<typename T>
T GCD(T a, T b);
void CalculateKeys();
ll encrypt(char c);
ll pow_a_b(ll a, ll b, ll mod);
char decrypt(ll n);

int main()
{
    CalculateKeys();
    cout<< "Your Message: ";
    cin>> msg;
    
    for(auto x: msg)
        en_msg.push_back(encrypt(x));

    for(auto x: en_msg)
        de_msg+= decrypt(x);
    // debug(dp);
    cout<< de_msg<< '\n';
}

void CalculateKeys()
{
    n= p*q;
    fin= (p-1)*(q-1);

    while(e<fin)
    {
        if(GCD<ll>(e, fin)==1) break;
        else e++;
    }
    debug(e);

    d= (k*fin +1)/e;
    dp= double((k*fin)+1)/double(e);
}

ll encrypt(char c)
{
    return pow_a_b(ll(c), e, n);
}

char decrypt(ll a)
{
    ll c= pow_a_b(a, d, n);
    char p= char(c);
    debug(c);
    if(c<256) return char(c);
    else return '*';
    // return char(pow_a_b(a, d, n));
}

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


template<typename T>
T GCD(T a, T b)
{
	if(!b) return a;
	return GCD(b, a%b);
}