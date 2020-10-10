#include <bits/stdc++.h>
#define N 200005
using namespace std;

struct suffix{
    int a[N];
    int sa[N],rk[N],height[N],tax[N],tp[N];
    int h[N],n,m;
    void rsort(){
        for(int i=0;i<=m;i++) tax[i]=0;
        for(int i=1;i<=n;i++) tax[rk[tp[i]]]++;
        for(int i=1;i<=m;i++) tax[i]+=tax[i-1];
        for(int i=n;i>=1;i--) sa[tax[rk[tp[i]]]--]=tp[i];
    }

    int cmp(int *f,int x,int y,int w){
        return f[x]==f[y]&&f[x+w]==f[y+w];
    }

    void getsa(int str[],int len){
        n=len;
        for(int i=1;i<=n;i++){
            a[i]=str[i];
        }
        for(int i=1;i<=n;i++){
            rk[i]=a[i];
            tp[i]=i;
        }
        m=127,rsort();
        for(int w=1,p=1,i;p<n;w+=w,m=p){
            for(p=0,i=n-w+1;i<=n;i++) tp[++p]=i;
            for(i=1;i<=n;i++) if(sa[i]>w) tp[++p]=sa[i]-w;

            rsort();
            swap(rk,tp);
            rk[sa[1]]=p=1;

            for(i=2;i<=n;i++)
                rk[sa[i]]=cmp(tp,sa[i],sa[i-1],w)?p:++p;
        }

        int j,k=0;
        for(int i=1;i<=n;h[rk[i++]]=k){
            for(k=k?k-1:k,j=sa[rk[i]-1];a[i+k]==a[j+k];++k);
        }
    }

    int st[N][20],len[N];

    void getst(){
        for(int i=1;i<=n;i++) st[i][0]=h[i];
        for(int k=1;(1<<k)<=n;k++){
            for(int i=1;i+(1<<k)-1<=n;i++){
                st[i][k]=min(st[i][k-1],st[i+(1<<(k-1))][k-1]);
            }
        }

        for(int i=1;i<=n;i++){
            len[i]=len[i-1];
            if(1<<(len[i]+1)<i) ++len[i];
        }
    }

    int query(int l,int r){
        int k=len[r-l+1];
        return min(st[l][k],st[r-(1<<k)+1][k]);
    }

    int lcp(int x,int y){
        if(x==y) return n-x+1;
        x=rk[x],y=rk[y];
        if(x>y) swap(x,y);
        x++; if (x>y) return 0;
        return query(x,y);
    }

    int aa=1,bb=1;
    void solve(){
        for(int i=2;i<=n;i++){
            int nowb=abs(sa[i]-sa[i-1]),nowa=nowb+h[i];
            if(1ll*nowa*bb>1ll*nowb*aa){
                aa=nowa; bb=nowb;
                int d=__gcd(aa,bb);
                aa/=d; bb/=d;
            }
        }
    }
}A,B;

char s[N];
int tmp[N];

int mxa=1,mxb=1,n;

void work(int lx,int rx,int l){
    int ry=A.lcp(lx,rx+1);
    int ly=B.lcp(n-rx+1,n-(lx-1)+1);
    lx-=ly; rx+=ry;
    int nowa=rx-lx+1;
    int nowb=l;
    if(1ll*nowa*mxb>1ll*nowb*mxa){
        mxa=nowa; mxb=nowb;
        int d=__gcd(mxa,mxb);
        mxa/=d; mxb/=d;
    }
}

int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++) tmp[i]=s[i];
    A.getsa(tmp,n);A.getst();
    reverse(tmp+1,tmp+n+1);
    B.getsa(tmp,n);B.getst();
    for(int l=1;l<=n/2;l++){
        int last=1;
        for(int i=1+l;i<=n;i+=l){
            if(A.lcp(i,last)>=l) continue;
            work(last,i-1,l);
            if(i+l-1<=n) last=i;
            else last=0;
        }
        if(last) work(last,n,l);
    }
    A.solve();
    if(1ll*A.aa*mxb<1ll*A.bb*mxa){
        printf("%d/%d\n",mxa,mxb);
    }else{
        printf("%d/%d\n",A.aa,A.bb);
    }

}

