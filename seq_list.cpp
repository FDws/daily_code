#include <iostream>

using namespace std;

template <class T>
class SeqList
{
private:
    T *data;
    T *temp;
    int length;
    int last;
public:
    SeqList(int n)
    {
        data = new T[n];
        last = -1;
        length = n;
    }
    void input_data()
    {
        int i;
        for (i=0; i<length; i++)
        {
            cin>>data[i];
            last++;
        }
    }
    void output()
    {
        int i;
        for (i=0; i<length;i++)
        {
            cout<<data[i]<<" ";
        }
        cout<<endl;
    }
    void re_new()
    {
        length = length + 1;
        temp = new T[length];
        int i;
        for (i=0; i<=last; i++)
        {
            temp[i] = data[i];
        }

        delete [] data;
        data = temp;
    }
    void insert_data(T x,int i)
    {
        re_new();
        int j;

        for (j=last+1; j>=i; j--)
        {
            data[j] = data[j-1];
        }

        data[i-1] = x;
        last++;

        output();
    }
    void delete_data(int i)
    {
        i--;
        for (; i<last; i++)
        {
            data[i] = data[i+1];
        }
        last--;
		length--;

        output();
    }

    void search_data(T x)
    {
        int i;
        for(i=0; i<length; i++)
        {
            if (data[i]==x)
            {
                cout<<i+1<<endl;
                break;
            }
        }

        if (i>last)
            cout<<"Not found"<<endl;
    }

    void inverse_data()
    {
        int i;
        int l;
        T tem;

        for (i=0,l=last; i<l; i++,l--)
        {
            tem = data[i];
            data[i] = data[l];
            data[l] = tem;
        }

        output();
    }

    int get_last()
    {
        return last;
    }
    void sort_data()
    {
        int i;
        int k;
        int j;
        T tem;

        for (i=0; i<last; i++)
        {
            k=i;
            for (j=i+1; j<=last; j++)
            {
                if (data[j]<data[k])
                {
                    k = j;
                }
            }
            if (k!=i)
            {
                tem = data[k];
                data[k] = data[i];
                data[i] = tem;
            }
        }

    }
    void add_list(const SeqList<T> se)
    {
        length = length+se.length;
        temp = new T[length];
        int j;
        int i;

        for (i=0; i<=last; i++)
        {
            temp[i] = data[i];
        }
        for (j=0; i<length; i++,j++)
        {
            temp[i] = se.data[j];
        }

        delete [] data;
        data = temp;

        last = length-1;

        sort_data();
        output();
    }
    ~SeqList()
    {
        delete [] data;
    }
};
int main()
{
    int n;
    int i;
    int x;

    cin>>n;
    SeqList<int> first(n);
    first.input_data();

    cin>>x>>i;
    first.insert_data(x,i);

    cin>>i;
    first.delete_data(i);

    cin>>x;
    first.search_data(x);

    first.inverse_data();

    cin>>n;
    SeqList<int> second(n);
    second.input_data();

    first.add_list(second);

    return 0;
}
