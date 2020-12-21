#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */
//#include <bitset>

bool doTheFlip ( char * src_data, int offset, int length, int channel, int bits, bool flipHorizontal, bool flipVertical, const char * dstFileName ) {
  int width;
  int height;
  unsigned char testik1;
  unsigned char testik2;
  if ( ! offset ) {
    testik1 = src_data[2];
    testik2 = src_data[3];
    //cout << bitset<8>((src_data[3] << 8)).to_ulong() << " | " << bitset<8>(testik) << endl;
    width = ((testik2 << 8) | testik1);
    testik1 = src_data[4];
    testik2 = src_data[5];
    height = (testik2 << 8) | testik1;
    //width = src_data[2];
  }
  else {
    testik1 = src_data[3];
    testik2 = src_data[2];
    //cout << bitset<8>((src_data[3] << 8)).to_ulong() << " | " << bitset<8>(testik) << endl;
    width = ((testik2 << 8) | testik1);
    testik1 = src_data[5];
    testik2 = src_data[4];
    height = (testik2 << 8) | testik1;
  }
  
    cout << width << ", " << height << endl;

  if (bits == 0) {
    int width_one = 0;
    if ( ! ((width*(channel+1)) % 8) ) {
      width_one = (width*(channel+1)) / 8;
      cout << "😂 : " << width_one << endl;
    }
    else {
      width_one = ((width*(channel+1)) / 8) + 1;
    }
    if ( (width_one*height != (length - 8)) || width < 1 || height < 1 || length < 9) {
    return false;
    }

    if ( flipHorizontal ) {
    int ind = 0;
    ind = 8;
    char *** onebit = new char ** [height]; 
    for(int i = 0; i < height; i++)
    {
      onebit[i] = new char * [width];
      for(int j = 0; j < width; j++)
      {
        onebit[i][j] = new char [channel+1];
      }
    }
    
    

    cout << "✝️" << channel << endl;
    
    int ind_i = 0;
    for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
      {
        for(int k = 0; k < channel+1; k++)
        {
         onebit[i][j][k] = ((src_data[ind] >> ind_i) & 0b01);
         //cout << "onebit" << i << "," << j << "," << k << ": " << onebit[i][j][k] << endl;
         if ( ind_i == 7 ) {
           ind_i = 0;
           ind++;
         }
         else {
           ind_i++;
         }
          
        }
        
      }
      if ( ind_i != 0 ){
      ind_i = 0;
      ind++;
      }
    }
    cout << "🤔" << endl;

    cout << "1 bit pole:" << endl;
    for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
      {
        for(int k = 0; k < channel+1; k++)
        {
          //cout << bitset<1>(onebit[i][j][k]);
        }
      }
      cout << endl;
    }

    char temp;
    for(int i = 0; i < height; i++)
    {
      for(int j = width-1; j >= (width/2); j--)
      {
        for(int k = 0; k < channel+1; k++)
        {
          temp = onebit[i][(width-1)-j][k];
          onebit[i][(width-1)-j][k] = onebit[i][j][k];
          onebit[i][j][k] = temp;
        }
        
      }
      
    }

    cout << "1 bit pole:" << endl;
    for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
      {
        for(int k = 0; k < channel+1; k++)
        {
          //cout << bitset<1>(onebit[i][j][k]);
        }
      }
      cout << endl;
    }
    
    char onebit_temp[8];
    int onebit_off = 0;

    char ** flipped_one = new char * [height];
    for(int i = 0; i < height; i++)
    {
     flipped_one[i] = new char [width_one];
    }
    
    int onebit_wid = 0;

    for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
      {
        for(int k = 0; k < channel+1; k++)
        {
          onebit_temp[onebit_off] = onebit[i][j][k];
          onebit_off++;
          //cout << "meme" << endl;
          if (onebit_off == 8){
            flipped_one[i][onebit_wid] = onebit_temp[7];
            //cout << "meme2" << endl;
            for(int l = 6; l >= 0; l--)
            {
              flipped_one[i][onebit_wid] = (flipped_one[i][onebit_wid] << 1 | onebit_temp[l]);
              //cout << "flipped: " << bitset<8>(flipped_one[i][onebit_wid]) << endl;
            }
            onebit_off = 0;
            onebit_wid++;
          }
          if ( j == width-1 && k == channel && onebit_off != 0 ) {
            cout << "😭" << endl;
            flipped_one[i][onebit_wid] = onebit_temp[onebit_off - 1];
          for(int l = onebit_off - 2; l >= 0; l--)
            {
              flipped_one[i][onebit_wid] = (flipped_one[i][onebit_wid] << 1 | onebit_temp[l]);
              //cout << "flipped: " << bitset<8>(flipped_one[i][onebit_wid]) << endl;
            }
            onebit_off = 0;
            onebit_wid++;
            }
        }
        
      }
      onebit_off = 0;
      onebit_wid = 0;
    }

    if (flipVertical){
      for(int i = height-1; i >= height/2; i--)
    {
      for(int j = 0; j < width_one; j++)
      {
        temp = flipped_one[(height-1)-i][j];
        flipped_one[(height-1)-i][j] = flipped_one[i][j];
        flipped_one[i][j] = temp;
      }
    }
    }

    ofstream onebitout (dstFileName, ofstream::binary);
    if (! onebitout.good()) {
      return false;
    }
    onebitout.write(src_data, 8);
    if (! onebitout.good()) {
      return false;
    }
    for(int i = 0; i < height; i++)
    {
       onebitout.write(flipped_one[i], width_one);
      for(int j = 0; j < width_one; j++)
      {
        //cout << "i: " << i << ", j: " << j << ",    : " << bitset<8>(flipped_one[i][j]) << endl;
      }
      
    }
    if (! onebitout.good()) {
      return false;
    }
    

  }
  
  if (flipVertical && ! flipHorizontal){
    char temp;
    int vert_i = 0;
    char ** flipped_one = new char * [height];
    for(int i = 0; i < height; i++)
    {
      flipped_one[i] = new char [width_one];
      for(int j = 0; j < width_one; j++)
      {
        flipped_one[i][j] = src_data[vert_i+8];
        vert_i++;
      }
    }
    for(int i = height-1; i >= height/2; i--)
    {
      for(int j = 0; j < width_one; j++)
      {
        temp = flipped_one[(height-1)-i][j];
        flipped_one[(height-1)-i][j] = flipped_one[i][j];
        flipped_one[i][j] = temp;
      }
    }
    
    ofstream onebitout (dstFileName, ofstream::binary);
    if (! onebitout.good()) {
      return false;
    }
    onebitout.write(src_data,8);
    if (! onebitout.good()) {
      return false;
    }
    for(int i = 0; i < height; i++)
    {
      onebitout.write(flipped_one[i], width_one);
      //cout << "✝️" << endl;
    }
    if (! onebitout.good()) {
      return false;
    }
    
  }
  if ( !flipHorizontal && !flipVertical ) {
    ofstream onebitout (dstFileName, ofstream::binary);
    if (! onebitout.good()) {
      return false;
    }
    onebitout.write(src_data,length);
    if (! onebitout.good()) {
      return false;
    }
  }
  
  
  }
  else {

  if ( (width * height * (channel+1) * (bits-2)) != (length - 8) || width < 1 || height < 1 || length < 10) {
    return false;
  }

  char * flipped = new char [length];
  int flipped_i = 0;
  for(flipped_i = 0; flipped_i < 8; flipped_i++) {
    flipped[flipped_i] = src_data[flipped_i];
  }
  //int width_off = 0;

  char **** src_new = new char *** [height];
  for(int i = 0; i < height; i++)
  {
    src_new[i] = new char ** [width];
    for(int j = 0; j < width; j++)
    {
      src_new[i][j] = new char * [4];
      for(int k = 0; k < 4; k++) {
        src_new[i][j][k] = new char [2];
      }
    }
  }
  
  int src_off = flipped_i;

  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      for(int k = 0; k < channel + 1; k++)
      {
        for(int l = 0; l < bits - 2; l++){
          src_new[i][j][k][l] = src_data[src_off];
          //cout << "src_new[" << i << "][" << j << "][" << k << "][" << l << "]: " << bitset<8>(src_data[src_off]) << endl;
          src_off++;
        }
      }
      
    }
    
  }
  

  if ( flipHorizontal && ! flipVertical ) {
  for(int i = 0; i < height; i++) {
    for(int j = width-1; j >= 0; j--)
    {
      for(int k = 0; k < channel+1; k++)
      {
        for(int l = 0; l < bits-2; l++)
        {
          //int help = (width*(channel+1)*j*l)-k+8-(i*(channel+1));
          //cout << "flipped[" << flipped_i << "]: " << bitset<8>(src_data[help]) << "  ( " << help << " )" << endl;
        flipped[flipped_i] = src_new[i][j][k][l];
        //cout << "src_new[" << i << "][" << j << "][" << k << "][" << l << "]: " << bitset<8>(src_data[src_off]) << endl;
        //cout << bitset<8>(src_new[i][j][k][l]) << endl;
        flipped_i++;
        }
      }
    }
  }
  cout << "✝️" << endl;
  ofstream imgfileout (dstFileName, ofstream::binary);
  if (! imgfileout.good()) {
      return false;
    }
  imgfileout.write(flipped,length);
  if (! imgfileout.good()) {
      return false;
  }
  }

  if ( flipVertical && ! flipHorizontal ) {
  for(int i = height-1; i >= 0; i--) {
    for(int j = 0; j < width; j++)
    {
      for(int k = 0; k < channel+1; k++)
      {
        for(int l = 0; l < bits-2; l++)
        {
          //int help = (width*(channel+1)*j*l)-k+8-(i*(channel+1));
          //cout << "flipped[" << flipped_i << "]: " << bitset<8>(src_data[help]) << "  ( " << help << " )" << endl;
        flipped[flipped_i] = src_new[i][j][k][l];
        //cout << "src_new[" << i << "][" << j << "][" << k << "][" << l << "]: " << bitset<8>(src_new[i][j][k][l]) << endl;
        //cout << bitset<8>(src_new[i][j][k][l]) << endl;
        flipped_i++;
        }
      }
    }
  }
  ofstream imgfileout (dstFileName, ofstream::binary);
  if (! imgfileout.good()) {
      return false;
    }
  imgfileout.write(flipped,length);
  if (! imgfileout.good()) {
      return false;
    }
  }

  if ( flipHorizontal && flipVertical ) {
    char **** flipped2 = new char *** [height];
    for(int i = 0; i < height; i++)
    {
      flipped2[i] = new char ** [width];
      for(int j = 0; j < width; j++)
      {
        flipped2[i][j] = new char * [4];
        for(int k = 0; k < 4; k++) {
          flipped2[i][j][k] = new char [2];
        }
      }
    }

    for(int i = 0; i < height; i++) {
    for(int j = width-1; j >= 0; j--)
    {
      for(int k = 0; k < channel+1; k++)
      {
        for(int l = 0; l < bits-2; l++)
        {
          //int help = (width*(channel+1)*j*l)-k+8-(i*(channel+1));
          //cout << "flipped[" << flipped_i << "]: " << bitset<8>(src_data[help]) << "  ( " << help << " )" << endl;
        flipped2[i][width-1-j][k][l] = src_new[i][j][k][l];
        //cout << "src_new[" << i << "][" << j << "][" << k << "][" << l << "]: " << bitset<8>(src_new[i][j][k][l]) << endl;
        //cout << bitset<8>(src_new[i][j][k][l]) << endl;
        }
      }
    }
  }

  /*for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      for(int k = 0; k < channel + 1; k++)
      {
        for(int l = 0; l < bits - 2; l++){
          //src_new[i][j][k][l] = src_data[src_off];
          cout << "flipped2[" << i << "][" << j << "][" << k << "][" << l << "]: " << bitset<8>(flipped2[i][j][k][l]) << endl;
          //src_off++;
        }
      }
      
    }
    
  }*/

  for(int i = height-1; i >= 0; i--) {
    for(int j = 0; j < width; j++)
    {
      for(int k = 0; k < channel+1; k++)
      {
        for(int l = 0; l < bits-2; l++)
        {
          //int help = (width*(channel+1)*j*l)-k+8-(i*(channel+1));
          //cout << "flipped[" << flipped_i << "]: " << bitset<8>(src_data[help]) << "  ( " << help << " )" << endl;
        flipped[flipped_i] = flipped2[i][j][k][l];
        //cout << "src_new[" << i << "][" << j << "][" << k << "][" << l << "]: " << bitset<8>(src_data[src_off]) << endl;
        //cout << bitset<8>(flipped2[i][j][k][l]) << endl;
        flipped_i++;
        }
      }
    }
  }

  ofstream imgfileout (dstFileName, ofstream::binary);
  if (! imgfileout.good()) {
      return false;
    }
  imgfileout.write(flipped,length);
  if (! imgfileout.good()) {
      return false;
  }

  for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
      {
        for(int k = 0; k < 4; k++) {
          delete[] flipped2[i][j][k];
        }
        delete[] flipped2[i][j];
      }
      delete[] flipped2[i];
    }
  delete[] flipped2;
  }


  

  if ( ! flipHorizontal && ! flipVertical ){
    cout << "hellou, my name is vladimir meloun" << endl;
    for(int i = 8; i < length; i++)
    {
      flipped[i] = src_data[i];
    }
    ofstream imgfileout (dstFileName, ofstream::binary);
    if (! imgfileout.good()) {
      return false;
    }
    imgfileout.write(flipped,length);
    if (! imgfileout.good()) {
      return false;
    }
    
  }
  delete[] flipped;
  //delete[] flipped2;
  }
  return true;
}


bool afterEnd ( char * src_data, int offset, int length, bool flipHorizontal, bool flipVertical, const char * dstFileName ) {
  int channel = src_data[6+offset] & ((1 << 2) - 1);
  cout << "channels: " << channel+1 << endl;
  if ( channel < 0 || channel == 1 || channel > 3 ) {
    return false;
  }
  
  int bits = (src_data[6+offset] >> 2);
  cout << "bits: " << pow(2.0,bits) << endl;
  if ( bits < 0 || bits == 2 || bits == 1 || bits > 4 ) {
    return false;
  }

  if ( ! doTheFlip(src_data, offset, length, channel, bits, flipHorizontal, flipVertical, dstFileName) )
  return false;

  return true;
}

bool loadFile ( const char * srcFileName, const char * dstFileName, bool flipHorizontal, bool flipVertical ) {
  ifstream imgfile (srcFileName, ifstream::binary);
  if ( ! imgfile.good() ) {
    return false;
  }
  

  if (imgfile.good()) {
    imgfile.seekg (0, imgfile.end);
    int length = imgfile.tellg();
    imgfile.seekg (0, imgfile.beg);
    
    char * src_data = new char [length];

    if (! imgfile.good()) {
      return false;
    }
    imgfile.read (src_data,length);
    if (! imgfile.good()) {
      return false;
    }
    
    for(int i = 0; i < length; i++)
    {

        //cout << bitset<8>(src_data[i]) << endl; 
    }

    /*cout << "endian: " << bitset<8>(src_data[0]) << ", " << bitset<8>(src_data[1]) << endl; 
    cout << "sirka: " << bitset<8>(src_data[3]).to_ulong() << ", " << bitset<8>(src_data[2]) << endl; 
    cout << "vyska: " << bitset<8>(src_data[5]).to_ulong() << ", " << bitset<8>(src_data[4]) << endl; 
    cout << "kodovanie: " << bitset<8>(src_data[7]) << ", " << bitset<8>(src_data[6]) << endl; 
    */

    cout << "length: " << length << endl;
    int endian = (src_data[0] << 8) | src_data[1];
    if ( endian == ENDIAN_LITTLE ) {
      cout << "little end" << endl;
      if ( ! afterEnd(src_data, 0, length, flipHorizontal, flipVertical, dstFileName) )
      return false;
    }
    else if ( endian == ENDIAN_BIG ){
      if ( ! afterEnd(src_data, 1, length, flipHorizontal, flipVertical, dstFileName) )
      return false;
    }
    else return false;
    
    delete[] src_data;

    return true;
}
else return false;
}

bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{
  if (! loadFile (srcFileName, dstFileName, flipHorizontal, flipVertical) ) 
  return false;
  else return true;
}

#ifndef __PROGTEST__
#include "compare.hpp"

int main ( void )
{
  /*assert ( flipImage ( "input_00.img", "output_00.img", true, false )
           && identicalFiles ( "output_00.img", "ref_00.img" ) );

  assert ( flipImage ( "input_04.img", "output_04.img", true, false )
           && identicalFiles ( "output_04.img", "ref_04.img" ) );

  assert ( flipImage ( "input_07.img", "output_07.img", true, false )
           && identicalFiles ( "output_07.img", "ref_07.img" ) );

  assert ( ! flipImage ( "input_09.img", "output_09.img", true, false ) );

  assert ( flipImage ( "input_01.img", "output_01.img", false, true )
           && identicalFiles ( "output_01.img", "ref_01.img" ) );

  assert ( flipImage ( "input_06.img", "output_06.img", false, true )
           && identicalFiles ( "output_06.img", "ref_06.img" ) );

  assert ( flipImage ( "input_03.img", "output_03.img", false, false )
           && identicalFiles ( "output_03.img", "ref_03.img" ) );

  assert ( flipImage ( "input_05.img", "output_05.img", true, true )
           && identicalFiles ( "output_05.img", "ref_05.img" ) );

  assert ( flipImage ( "input_02.img", "output_02.img", true, true )
           && identicalFiles ( "output_02.img", "ref_02.img" ) );

  assert ( flipImage ( "input_08.img", "output_08.img", true, true )
           && identicalFiles ( "output_08.img", "ref_08.img" ) );

  // extra inputs (optional & bonus tests)
  assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
           && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
  assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
           && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
  assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
           && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
  assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
           && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
  assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
           && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
  assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
           && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
  assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
           && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
  */
  assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
           && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
  assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, true )
           && identicalFiles ( "extra_out_08.img", "testicek.img" ) );
  assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
           && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
  assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
           && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );

  return 0;
}
#endif /* __PROGTEST__ */
