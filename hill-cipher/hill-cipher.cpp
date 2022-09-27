#include <iostream>
using namespace std;

int key[3][3]; // Mendefinisikan matrik array 3x3

// Fungsi modula, membagi nilai sebanyak alphabet yang ada yaitu 26
int mod26(int x){
 return x >= 0 ? (x % 26) : 26 - (abs(x) % 26);
}

// Fungsi untuk mencari determinan matriks
int findDet(int m[3][3], int n){
 int det;
 if (n == 2) {// Jika  matrik index 2x2
  // Rumus mencari determinan
  det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
 }
 else if (n == 3) // Jika matrik index 3x3
 {
  // Rumus mencari determinan
  det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
 }
 else
  det = 0;
 return mod26(det); // Mengembalikan nilai det yang telah dibagi modula
}

// Fungsi mencari invers dari determinan
int findDetInverse(int R, int D = 26){
 int i = 0;
 int p[100] = {0, 1};
 int q[100] = {0};

 while (R != 0){
  q[i] = D / R;
  int oldD = D;
  D = R;
  R = oldD % R;
  if (i > 1)
  {
   p[i] = mod26(p[i - 2] - p[i - 1] * q[i - 2]);
  }
  i++;
 }
 if (i == 1)
  return 1;
 else
  return p[i] = mod26(p[i - 2] - p[i - 1] * q[i - 2]);
}

// Fungsi untuk perkalian matriks
void multiplyMatrices(int a[1000][3], int a_rows, int a_cols, int b[1000][3], int b_rows, int b_cols, int res[1000][3])
{
 for (int i = 0; i < a_rows; i++){
  for (int j = 0; j < b_cols; j++){
   for (int k = 0; k < b_rows; k++){
    res[i][j] += a[i][k] * b[k][j];
   }
   res[i][j] = mod26(res[i][j]);
  }
 }
}

// Fungsi membuat invers pada matriks
void findInverse(int m[3][3], int n, int m_inverse[3][3]){
 int adj[3][3] = {0};

 int det = findDet(m, n);
 int detInverse = findDetInverse(det);

 if (n == 2){
  adj[0][0] = m[1][1];
  adj[1][1] = m[0][0];
  adj[0][1] = -m[0][1];
  adj[1][0] = -m[1][0];
 }
 else if (n == 3)
 {
  int temp[5][5] = {0};

  for (int i = 0; i < 5; i++)
  {
   for (int j = 0; j < 5; j++)
   {
    temp[i][j] = m[i % 3][j % 3];
   }
  }

  for (int i = 1; i <= 3; i++)
  {
   for (int j = 1; j <= 3; j++)
   {
    adj[j - 1][i - 1] = temp[i][j] * temp[i + 1][j + 1] - temp[i][j + 1] * temp[i + 1][j];
   }
  }
 }

 for (int i = 0; i < n; i++)
 {
  for (int j = 0; j < n; j++)
  {
   m_inverse[i][j] = mod26(adj[i][j] * detInverse);
  }
 }
}

// C = PK
// Fungsi mengenkripsi plaintext
string encrypt(string pt, int n)
{
 int P[1000][3] = {0};
 int C[1000][3] = {0};
 int ptIter = 0;

 while (pt.length() % n != 0)
 {
  pt += "x";
 }
 int row = (pt.length()) / n;
 for (int i = 0; i < row; i++)
 {
  for (int j = 0; j < n; j++)
  {
   P[i][j] = pt[ptIter++] - 'a';
  }
 }

 multiplyMatrices(P, row, n, key, n, n, C);

 string ct = "";
 for (int i = 0; i < row; i++)
 {
  for (int j = 0; j < n; j++)
  {
   ct += (C[i][j] + 'a');
  }
 }
 return ct;
}

// Fungsi mendeskripsikan ciphertext
// P = C*(k_inverse)
string decrypt(string ct, int n)
{
 int P[1000][3] = {0};
 int C[1000][3] = {0};
 int ctIter = 0;

 int row = ct.length() / n;

 for (int i = 0; i < row; i++)
 {
  for (int j = 0; j < n; j++)
  {
   C[i][j] = ct[ctIter++] - 'a';
  }
 }

 int k_inverse[3][3] = {0};

 findInverse(key, n, k_inverse);

 multiplyMatrices(C, row, n, k_inverse, n, n, P);

 string pt = "";
 for (int i = 0; i < row; i++)
 {
  for (int j = 0; j < n; j++)
  {
   pt += (P[i][j] + 'a');
  }
 }
 return pt;
}

void printMatrix(int key[3][3], int size)
{
 for (int i = 0; i < size; i++)
 {
  for (int j = 0; j < size; j++)
  {
   cout << key[i][j] << " ";
  }
  cout << "\n";
 }
}

int main()
{
 string pt, ct;
 int n, y, count;

 do
 {
  cout << "\n-=-=-=-=-=- PROGRAM HILL CIPHER -=-=-=-=-=-" << endl;
  cout << "1. ENKRIPSI\n2. DEKRIPSI\n3. MENCARI KEY\n4. EXIT\n";
  cout << "Masukan Pilihan  : ";
  cin >> y;
  int c[1000][3] = {0};
  int p[1000][3] = {0};
  int res[1000][3] = {0};
  switch (y)
  {
  case 1:
   cout << "Masukan Plaintext(lowercase) : ";
   cin.ignore(100, '\n');
   getline(cin, pt);
   cout << "Ukuran Key Matrik  : ";
   cin >> n;
   cout << "Masukan Key Matrik  : " << endl;
   for (int i = 0; i < n; i++)
   {
    for (int j = 0; j < n; j++)
    {
     cout << "key[" << i + 1 << "][" << j + 1 << "] : ";
     cin >> key[i][j];
    }
   }
   cout << "KEY  : \n";
   printMatrix(key, n);
   cout << "ENKRIPSI : " << encrypt(pt, n) << endl;
   break;
  case 2:
   cout << "Masukan Ciphertext(lowercase) : ";
   cin.ignore(100, '\n');
   getline(cin, ct);
   cout << "Ukuran Key Matrik  : ";
   cin >> n;
   cout << "Masukan Key Matrik  : " << endl;
   for (int i = 0; i < n; i++)
   {
    for (int j = 0; j < n; j++)
    {
     cout << "key[" << i + 1 << "][" << j + 1 << "] : ";
     cin >> key[i][j];
    }
   }
   cout << "KEY  : \n";
   printMatrix(key, n);
   cout << "DEKRIPSI : " << decrypt(ct, n) << endl;
   break;
  case 3:
   cin.ignore();
   cout << "==================================\n";
            cout << "\nInput Plaintext: ";
            getline(cin, pt);
            cout << "Input Ciphertext: ";
            getline(cin, ct);
   cout << "----------------------------------\n";
   cout << "Ukuran Key Matrik  : ";
   cin >> n;
            count = 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    //Mendapatkan matriks C dari ciphertext
     c[j][i] = ct[count] - 'a';
     //Mendapatkan matriks P dari plaintext
     p[j][i] = pt[count] - 'a';
     count++;
                }
            }
   int p_inverse[3][3];
            //Melakukan invers pada matriks P
            findInverse(p, n, p_inverse);
            // Matriks C dikalikan dengan matriks P invers
   multiplyMatrices(c,n,n,p,n,n,res);

   cout << "\n----------------------------------\n";
            cout << "\nKunci Hill Cipher: \n";
            printMatrix(key, n);
            break;
  default:
   break;
  }
 } while (y != 4);
}