#include <ijvm.h>

int counter = 0;

int init_ijvm(char *binary_file)
{
  FILE *fp;

  fp = fopen(binary_file, "rb");

  int size_array = 0;
  int indic = 0; // variable that keeps track of const pool data size + current array pointer

  fseek(fp, 0L, SEEK_END);
  size_array = ftell(fp);
  rewind(fp);

  byte_t array[size_array];
  byte_t byte;

  word_t const_size;
  word_t magic_num;
  word_t text_size;



  while (true)
  {
    byte = fgetc(fp);

    if (feof(fp)) {break;}

    counter += 1;
    array[counter] = byte;

    if (counter == 4)
    {
      magic_num = (array[counter - 3] << 24) + (array[counter - 2] << 16) + (array[counter - 1] << 8) + array[counter];
    }

    if (counter == 12)
    {
      const_size = (array[counter - 3] << 24) + (array[counter - 2] << 16) + (array[counter - 1] << 8) + array[counter];
      indic += const_size;
      indic += 20; // indicates next relevant pointer = magic_num + const origin + const pool size + text origin + text size
    }

    if (counter == indic)
    {
      text_size = (array[counter - 3] << 24) + (array[counter - 2] << 16) + (array[counter - 1] << 8) + array[counter];
    }

  } // while end

  for (int i = 1; i < size_array + 1; i++)
  {
    printf("%x", array[i]);
  }

  printf("\n%x\n", magic_num);
  printf("%x\n", const_size);
  printf("%x\n", text_size);

  for (int opcode = indic ; opcode <= indic + text_size; opcode++)
  {
    switch (array[opcode])
    {
      case OP_BIPUSH:
        printf("%s\n", "BIPUSH");
        opcode += 1;
        break;

      case OP_IADD:
        printf("%s\n", "IADD");
        break;

      case OP_OUT:
        printf("%s\n", "OUT");
        break;

      case OP_HALT:
        printf("%s\n", "HALT");
        break;
    }
    counter += 1;
  }

  return 0;
}

bool step(void)
{
  return true;
}

int text_size(void)
{
  return 0;
}

byte_t *get_text(void)
{
  return 0;
}

int get_program_counter(void)
{
  return counter;
}

byte_t get_instruction(void)
{
  return 0;
}

void destroy_ijvm()
{
  // Reset IJVM state
}

void run()
{
  // Step while you can
}

void set_input(FILE *fp)
{
  // TODO: implement me
}

void set_output(FILE *fp)
{
  // TODO: implement me
}
