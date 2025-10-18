#include<bits/stdc++.h>
#include<zlib.h>



std::string base64_decode(std::string const& encoded_string);


int main(){
    std::string b64;
    std::cout << "Enter base64 data: ";
    std::getline(std::cin, b64);
    std::string f64 = "";
    for(char c : b64){
        switch (c)
        {
        case '2': // 2 -> 1
            f64 += "1";
            break;
        case 'a': // a -> 2
            f64 += "2";
            break;
        case '1': // 1 -> a
            f64 += "a";
            break;
        default:
            f64 += c;
            break;
        }
    }

    std::string str = base64_decode(f64);
    unsigned char* p = reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));

    z_streamp strm = (z_streamp)(malloc(sizeof(z_stream_s)));

    strm->avail_in = str.length();
    strm->next_in = p;
    unsigned char outBuffer[129]{0};
    strm->next_out = outBuffer;
    strm->avail_out = 128;
    
    {
      int ret = inflateInit2(strm, -MAX_WBITS);
      if(ret != Z_OK){
        std::cout << "inflateInit returned: " << ret << "\n";
        return 0;
      }
    }

    int ret = 0;
    std::string ans;
    do{
        ret = inflate(strm, Z_NO_FLUSH);
        if(ret != Z_STREAM_END && ret != Z_OK){
          std::cout << "failed. (inflate returned: " << ret << ")\n";
          return 0;
        }

        ans += reinterpret_cast<const char*>(outBuffer);
        memset(outBuffer, 0, sizeof(outBuffer));

        strm->next_out = outBuffer;
        strm->avail_out = 128;
    }while(ret != Z_STREAM_END);
    
    // std::cout << "decoded: " << strm->total_out << "\n";
    std::cout << ans;

    return 0;
}


static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";
static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}
std::string base64_decode(std::string const& encoded_string) {
  size_t in_len = encoded_string.size();
  size_t i = 0;
  size_t j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i == 4) {
      for (i = 0; i < 4; i++)
        char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 4; j++)
      char_array_4[j] = 0;

    for (j = 0; j < 4; j++)
      char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}