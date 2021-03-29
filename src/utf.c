i32 utf8_len(u8 ch) {
  if (ch<128)           return 1;
  if ((ch>>5)==  0b110) return 2;
  if ((ch>>4)== 0b1110) return 3;
  if ((ch>>3)==0b11110) return 4;
  return -1;
}
u32 utf8_p(u8* p) {
  i32 len = utf8_len(*p);
  switch (len) { default: UD;
    case -1: return (u32)-1;
    case  1: return *p;
    case  2: return (0b11111&*p)<< 6  |  (0b111111&p[1]);
    case  3: return (0b1111 &*p)<<12  |  (0b111111&p[2]) | (0b111111&p[1])<<6;
    case  4: return (0b111  &*p)<<18  |  (0b111111&p[3]) | (0b111111&p[2])<<6 | (0b111111&p[1])<<12;
  }
}
B fromUTF8(char* s, u64 len) {
  u64 sz = 0;
  u64 j;
  for (j = 0; j < len; j+= utf8_len(s[j])) sz++;
  if (j!=len) return err("invalid UTF-8");
  HArr_p r = m_harrv(sz);
  u64 p = 0;
  for (u64 i = 0; i < len; i+= utf8_len(s[i])) r.a[p++] = m_c32(utf8_p((u8*)s+i)); // may read after end, eh
  return r.b;
}