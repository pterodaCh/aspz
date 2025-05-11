enum {N=32};
int a[N], pfx[N];
void prefix_sum()
{
    int i, accum;
    for (i=0, accum=a[0]; i < N; i++, accum+=a[i])
    pfx[i] = accum;
}
int main() 
{
    prefix_sum();
}
