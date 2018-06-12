#include <ijvm.h>
#include <stdlib.h>
#include <assert.h>


int counter = 0;


byte_t *text_data;
word_t *const_data;

word_t size_text;



static word_t swap_uint32(word_t num)
{
  return ((num>>24)&0xff) | ((num<<8)&0xff0000) |
  ((num>>8)&0xff00) |  ((num<<24)&0xff000000);
}

word_t read_word(FILE *fp)
{
  word_t value;

  fread(&value, sizeof(word_t), 1, fp);
  return swap_uint32(value);
}


int init_ijvm(char *binary_file)
{
  FILE *fp;

  fp = fopen(binary_file, "rb");
  assert(fp != NULL);

  word_t magic_num    = read_word(fp);
  assert(magic_num == MAGIC_NUMBER);

  word_t const_origin = read_word(fp);
  word_t const_size   = read_word(fp);
  const_data = malloc(const_size);

  for (word_t i = 0; i < const_size / 4; i++)
  {
    const_data[i] = (word_t) read_word(fp);
  }

  word_t text_origin = read_word(fp);
  size_text   = read_word(fp);
  text_data = malloc(size_text);

  fread(text_data, sizeof(byte_t), size_text, fp);

  fclose(fp);


  return 0;
}

char* match(int counter)
{
  char *opcode;
    switch (text_data[counter])
    {
      case OP_BIPUSH:
        opcode = "BIPUSH";
        counter++;
        break;
      case OP_DUP:
        opcode = "DUP";
        break;
      case OP_ERR:
        opcode = "ERR";
        break;
      case OP_GOTO:
        opcode = "GOTO";
        break;
      case OP_HALT:
        opcode = "";
        break;
      case OP_IADD:
        opcode = "IADD";
        break;
      case OP_IAND:
        opcode = "IAND";
        break;
      case OP_IFEQ:
        opcode = "IFEQ";
        break;
      case OP_IFLT:
        opcode = "IFLT";
        break;
      case OP_ICMPEQ:
        opcode = "ICMPEQ";
        break;
      case OP_IINC:
        opcode = "IINC";
        break;
      case OP_ILOAD:
        opcode = "ILOAD";
        break;
      case OP_IN:
        opcode = "IN";
        break;
      case OP_INVOKEVIRTUAL:
        opcode = "INVOKEVIRTUAL";
        break;
      case OP_IOR:
        opcode = "IOR";
        break;
      case OP_IRETURN:
        opcode = "IRETURN";
        break;
      case OP_ISTORE:
        opcode = "ISTORE";
        break;
      case OP_ISUB:
        opcode = "ISUB";
        break;
      case OP_LDC_W:
        opcode = "LDC_W";
        break;
      case OP_NOP:
        opcode = "NOP";
        break;
      case OP_OUT:
        opcode = "OUT";
        break;
      case OP_POP:
        opcode = "POP";
        break;
      case OP_SWAP:
        opcode = "SWAP";
        break;
      case OP_WIDE:
        opcode = "WIDE";
        break;
      default:
        opcode="";
        break;
    }
      return opcode;
}





bool step(void)
{
  printf("%s\n", match(counter));
  counter += 1;
  return true;
}

int text_size(void) // done
{
  return size_text;
}

byte_t *get_text(void) // TODO
{
  return text_data;
}

int get_program_counter(void) // done
{
  return counter;
}

byte_t get_instruction(void)
{
  return 0;
}

void destroy_ijvm()
{
  counter = 0;
  free(text_data);
  free(const_data);
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
