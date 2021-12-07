#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll alfa, prm=101;



ll power(ll a, ll b, ll mod)
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

bool check(ll m,ll g){
	cout<<g<<"\n\n";
	for(int i=1;i<=(m-2);i++){
		cout<<power(g,m,i)<<"\n";
	}
	return 0;
}

ll find_primitive_root(ll m){
	for(ll i=2;i<m;i++){
		if(__gcd(i,m)==1){
		if(check(m,i))
		return i;
		}

	
	}
	return -1;

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

int main(){
	int a = 3, b = 4;
    input:
	cout<<"Enter the value of alfa :";
	cin>>alfa;

	// p = find_primitive_root(m);

	bool prr[prm];
    for(int i=0; i<prm; i++) prr[i]= 0;
    for(int i=0; i<prm-1; i++)
        prr[pow_a_b(alfa, i, prm)]=1;

    for(int i=1; i<prm; i++) 
        if(!prr[i]) 
        {
            cout<< i<< '\n';
            cout<< "alfa is not a premitive root of "<< prm<< '\n';
            // return 0;
            goto input;
        }
    
	cout<<"Public keys : "<<"p : "<<alfa<<" g: "<<prm<<"\n";
    cout<<"Alice's private key : "<<a<<"\n";
    cout<<"Bob's private key : "<<b<<"\n";

    ll A = power(prm,a,alfa);
    ll B = power(prm,b,alfa);
    cout<<"Alice's generated key : "<<A<<"\n";
	cout<<"Bob's generated key : "<<B<<"\n";

    cout<<"Alice's secret key : "<<power(B,a,alfa)<<"\n";
    cout<<"Bob's secret key : "<<power(A,b,alfa)<<"\n";

	
	
	
	
}