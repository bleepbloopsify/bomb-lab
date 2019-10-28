#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

size_t stage = 0;
char* password = "welcometothebss!Thisiswhereweputabunchofglobalsifweneedthem";
size_t number_of_explosions = 0;
char encrypted[] = { 0x95, 0xe6, 0x63, 0x94, 0xf1, 0x75, 0x96, 0xe6, 0x61, 0x9c, 0xe7, 0x67, 0xac, 0xfe, 0x6d, 0xac, 0xf3, 0x6d, 0x86, 0xf8, 0x5d, 0x95, 0xe3, 0x70, 0x80, 0xfe, 0x5d, 0x87, 0xeb, 0x71, 0x87, 0xef, 0x5d, 0x9c, 0xec, 0x5d, 0x81, 0xef, 0x74, 0x96, 0xf8, 0x71, 0x9a, 0xe4, 0x65, 0xac, 0xf3, 0x6d, 0x86, 0xe4, 0x65, 0xac, 0xfa, 0x63, 0x97, 0xeb, 0x75, 0x92, 0xe4, 0x5d, 0x90, 0xe5, 0x6f, 0x96, 0xd5, 0x76, 0x9c, 0xd5, 0x6d, 0x80, 0xe3, 0x70, 0x9a, 0xf9, 0x5d, 0x95, 0xe5, 0x70, 0xac, 0xe7, 0x6d, 0x81, 0xef, 0x7f };

void explode() {
  puts("booooom");

  // TODO: fire some network request that reports on explosions

  exit(1);
}

void noLeavingAllowed(int dummy) {
  puts("Nice try");
  sleep(1);
  printf(".");
  sleep(1);
  printf(".");
  sleep(1);
  printf(".");

  puts("Just kidding! Bye bye");
  exit(1);
}

__attribute__((constructor))void init() {
  puts("beep beep defuse me");

  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0); 

  // alarm(20);
  // signal(SIGINT, noLeavingAllowed);
}

__attribute__((constructor)) void lit() {
  size_t prev_alarm;

  prev_alarm = alarm(20);
  if (prev_alarm != 20) {
    explode();

  }
}

void checkStage(size_t curr_stage) {
  if (curr_stage != stage) {
    puts("Oops! Wrong wire :(");
    explode();
  }
}

void pass() {
  puts("Nice! Onto the next one!");
  stage += 1;
}

void checkpassword() {
  char input[60];

  printf("Enter the password:");

  read(0, input, 59);
  input[59] = 0; // null byte

  if (strcmp(input, password) != 0) {
    puts("Wrong password! Open the binary >(\n");
    puts("You should be glad it didn't explode right away");
    exit(1);
  }

  pass();
}

int stage1() {
  char input[0x20];
  int key;

  puts("Stage 1");
  checkStage(1);

  fgets(input, 0x20, stdin);
  
  key = atoi(input);

  key ^= 5;
  key *= 25;
  key ^= 0xffffffff;

  if (key != -701) {
    explode();
  }

  pass();

  return key;
}

// this is fib
int yeet(int count) {
  if (count < 2) {
    return 1; 
  }
  return yeet(count - 1) + yeet(count - 2);
}

int stage2() {
  char input[0x20];
  int count;
  int result;

  puts("Stage 2");
  checkStage(2);

  fgets(input, 0x20, stdin);
  count = atoi(input);

  result = yeet(count);

  if (result != 987) {
    explode();
  }

  pass();

  return count * result;
}



typedef struct _Node {
  int value;
  struct _Node* next;
} Node;

Node a = { 0, NULL };
Node b = { 30, &a };
Node c = { 40, &b };
Node d = { 270, &c };
Node e = { 512, &d };
Node f = { 1024, &e };
Node g = { 2048, &f };
Node h = { 1, &g };

Node* bucket = &h;

int stage3() {
  char input[0x20];
  size_t index = 0;
  int multiplier = 0;
  size_t sum = 0;
  Node* curr;

  puts("Stage 3");
  checkStage(3);

  fgets(input, 0x20, stdin);
  index = atoi(input);

  fgets(input, 0x20, stdin);
  multiplier = atoi(input);

  curr = bucket;
  for (int idx = 0; idx < index && curr->next; ++idx) curr = curr->next;
  
  curr->value *= multiplier;

  curr = bucket;
  while(curr->next) {
    sum += curr->value;
    curr = curr->next;
  }

  if (sum != 4285) {
    explode();
  }

  pass();

  return index * multiplier;
}

typedef struct _BinaryNode {
  int key;
  int value;
  struct _BinaryNode* left;
  struct _BinaryNode* right;
} BinaryNode;

BinaryNode i = { 29, 0xdeadbeef, NULL, NULL };
BinaryNode j = { 31, 0x1337, NULL, NULL };
BinaryNode k = { 30, 0xaaaa, &i, &j };

BinaryNode l = { 255, 0xbb, NULL, NULL };
BinaryNode m = { 200, 0xff, NULL, NULL }; 
BinaryNode n = { 220, 0x30, &m, &l };

BinaryNode o = { 102, 0x7fffff, &k, &n };
BinaryNode* top = &o;

int yoint(int key, BinaryNode* curr) {
  if (!curr) return -1;
  if (key == curr->key) {
    return curr->value;
  } else if (key > curr->key) {
    return yoint(key, curr->right);
  } else {
    return yoint(key, curr->left);
  }
}

int stage4() {
  char input[0x20];
  int key;
  int result;

  puts("Stage 4");
  checkStage(4);

  fgets(input, 0x20, stdin);
  key = atoi(input);

  result = yoint(key, top);

  if (result != 0x1337) {
    explode();
  }

  pass();

  return key * result;
}

int main() {
  char input[0x20];
  int bytes_read;
  int choice;

  int key = 0;

  checkpassword();
  
  while (1) {
    puts("Cut the wire");
    printf(">");
    bytes_read = read(0, input, 0x1f);
    input[bytes_read] = 0;
    choice = atoi(input);

    switch(choice) {
      case 1: key += stage1(); break;
      case 2: key += stage2(); break;
      case 3: key += stage3(); break;
      case 4: key += stage4(); break;
    }

    if (stage == 5) break;
  }

  char* _key = (char*)&key;

  for (int idx = 0; idx < 84; ++idx) {
    encrypted[idx] = encrypted[idx] ^ _key[idx % 3];
  }

  printf("%s", encrypted);


  return 0;
}