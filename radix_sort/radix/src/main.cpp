#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int random_range(int begin, int end) {
    int range = end - begin + 1;
    return (rand() % range + begin);
}

void print_array(const vector<int>& a) {
    cout << "[";
    for(int i=0; i < a.size(); i++) {
        cout << a[i] << ", ";
    }

    cout << "]" << endl;
}

int radix_sort(const vector<int>& vin, vector<int>& vout) {

    //vout
    vout.resize(vin.size());

    //vtemp
    vector<int> vtemp;
    vtemp.insert(vtemp.begin(), vin.begin(), vin.end());

    //positions
    int base = 10;
    int buckets[10];
    int offsets[10];

    //sort each radix position
    int temp = -1;

    int count_zeros = 0;
    int npass = 1;

    //compute all buckets sizes
    while(count_zeros < vin.size()) {

        //reset
        count_zeros = 0;

        //reset
        for(int i=0; i < base; i++) {
            buckets[i] = 0;
            offsets[i] = 0;
        }

        //count buckets
        for(int i=0; i < vin.size(); i++) {
            temp = vtemp[i];

            int key = 0;
            for(int i=0; i < npass; i++) {
                temp = temp / base;
                key = temp % base;
            }

            //incr
            buckets[key]++;
        }

        //prefix-sum
        offsets[0] = 0;
        for(int i=1; i < base; i++) {
            offsets[i] = offsets[i-1] + buckets[i-1];
        }

        //reset buckets
        for(int i=0; i < base; i++) {
            buckets[i] = 0;
        }

        for(int i=0; i < vin.size(); i++) {
            temp = vtemp[i];

            int key = 0;
            for(int i=0; i < npass; i++) {
                temp = temp / base;
                key = temp % base;
            }

            if(temp == 0)
                count_zeros++;

            vout[ offsets[key] + buckets[key] ] = vtemp[i];
            buckets[key]++;
        }

        vtemp = vout;

        cout << "pass " << npass << " = ";
        print_array(vtemp);
        npass++;
    }


    //output
    return npass;
}

int main(int argc, char *argv[])
{
    srand(0);

    int len = 20;
    vector<int> vin;
    vin.resize(len);

    for(int i=0; i < len; i++) {
        vin[i] = random_range(0, 1000);
    }

    //input
    cout << "input ";
    print_array(vin);

    vector<int> vout;
    radix_sort(vin, vout);

    cout << "output ";
    print_array(vout);

    return 0;
}
