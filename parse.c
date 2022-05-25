/* parse.c - parsing and parse tree construction */

#include "project04.h"


void parse_table_init(struct parse_table_st *pt) {
    pt->len = 0;
}

// "Allocate" a parse node from the table of parse nodes
struct parse_node_st * parse_node_new(struct parse_table_st *pt) {
    struct parse_node_st *np;

    np = calloc(1, sizeof(struct parse_node_st));
    pt->len += 1;

    return np;
}

void parse_error(char *err) {
    printf("parse_error: %s\n", err);
    exit(-1);
}

// These are names of operators for printing
char *parse_oper_strings[] = {"PLUS", "MINUS", "MULT", "DIV","RSHIFT", "LSHIFT", "NOT", "AND", "OR", "XOR"};

// Print the dots which represent tree dept h in the output
void parse_tree_print_indent(int level) {
    level *= 2;
    for (int i = 0; i < level; i++) {
        printf(".");
    }
}

// Traverse the tree recursively to print out the structs
void parse_tree_print_expr(struct parse_node_st *np, int level) {
    parse_tree_print_indent(level);
    printf("EXPR ");

    // TODO: add support for oper1 --What is operation 1's rules?!!??!
    //check for left paren


    if (np->type == EX_INTVAL) {
        printf("INTVAL %d\n", np->intval.value);
    } else if (np->type == EX_OPER2) {
        printf("OPER2 %s\n", parse_oper_strings[np->oper2.oper]);
        parse_tree_print_expr(np->oper2.left, level+1);
        parse_tree_print_expr(np->oper2.right, level+1);
    }
    else if(np->type == EX_OPER1){
        printf("OPER1 %s\n", parse_oper_strings[np->oper1.oper]);
        parse_tree_print_expr(np->oper1.operand, level+1);
    }
}

void parse_tree_print(struct parse_node_st *np) {
    parse_tree_print_expr(np, 0);
}

// Parse the "program" part of the EBNF
// A program is composed of an expression followed by EOT
struct parse_node_st * parse_program(struct parse_table_st *pt,
                                        struct scan_table_st *st) {
    struct parse_node_st *np1;

    np1 = parse_expression(pt, st);

    if (!scan_table_accept(st, TK_EOT)) {
        parse_error("Expecting EOT");
    }

    return np1;
}

// Build the tree for expressions
// Expressions are defined in the EBNF as an operator followed
// by zero or more operator operand pairs
struct parse_node_st * parse_expression(struct parse_table_st *pt, struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np1, *np2;

    np1 = parse_operand(pt, st);

    while (true) {
        tp = scan_table_get(st, 0);
        if (tp->id == TK_PLUS) {
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_PLUS;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
        }
        else if(tp-> id == TK_MINUS){
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_MINUS;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
        }
        else if(tp-> id == TK_MULT){
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_MULT;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt,st);
            np1 = np2;
        }
        else if(tp-> id == TK_DIV){
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_DIV;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
        }
        else if(tp-> id == TK_LSHIFT){
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_LSL;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
         }
         else if(tp-> id == TK_RSHIFT){
             scan_table_accept(st, TK_ANY);
                 np2 = parse_node_new(pt);
             np2->type = EX_OPER2;
             np2->oper2.oper = OP_RSR;
             np2->oper2.left = np1;
             np2->oper2.right = parse_operand(pt, st);
             np1 = np2;
         }

         else if(tp-> id == TK_NOT){
             scan_table_accept(st, TK_ANY);
             np2 = parse_node_new(pt);
             np2->type = EX_OPER2;
             np2->oper2.oper = OP_NOT;
             np2->oper2.left = np1;
             np2->oper2.right = parse_operand(pt, st);
             np1 = np2;
         }

         else if(tp-> id == TK_OR){
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_OR;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
           }

         else if(tp-> id == TK_AND){
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_AND;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
         }
        else if(tp-> id == TK_XOR){
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = OP_XOR;
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
         }
         else {
            break;
        }

    }

    return np1;
}

int string_to_int(char * str, int base){
        int indexValue = 1;
        int len = strlen(str);
        int finalVal = 0;
        for(int i = len; i >= 0; i--){
                char currentDigit;
                int hexChar;
                if(str[i] == '0' || str[i]== '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9' || str[i] == 'A' || str[i] == 'a' || str[i] == 'B' || str[i] == 'b' || str[i] == 'C' || str[i] == 'c' || str[i] == 'd' || str[i] == 'D' || str[i] == 'e' || str[i] == 'E' || str[i] == 'f' || str[i] == 'F'){
                        if(str[i] == 'f' || str[i] == 'F' ){
                                hexChar = 15;
                                finalVal += hexChar * indexValue;
                                indexValue *= base;
                                continue;
                        }
                        if(str[i] == 'e' || str[i] == 'E' ){
                                hexChar = 14;
                                finalVal += hexChar * indexValue;
                                indexValue *= base;
                                continue;
                                                }
                        if(str[i] == 'd' || str[i] == 'D' ){
                                hexChar = 13;
                                finalVal += hexChar * indexValue;
                                indexValue *= base;
                                continue;
                                }
                        if(str[i] == 'c' || str[i] == 'C' ){
                                hexChar = 12;
                                finalVal += hexChar * indexValue;
                                indexValue *= base;
                                continue;
                                }
                        if(str[i] == 'b' || str[i] == 'B' ){
                                hexChar = 11;
                                finalVal += hexChar * indexValue;
                                indexValue *= base;
                                continue;
                                }
                        if(str[i] == 'a' || str[i] == 'A' ){
                                hexChar = 10;
                                finalVal += hexChar * indexValue;
                                indexValue *= base;
                                continue;
                                                }
                        currentDigit = str[i];
                        currentDigit -= '0';
                        finalVal += currentDigit * indexValue;
                        indexValue *= base;
                }
        }
        return finalVal;
}

char *reverseString(char* reversedString){

        int i;
        int length = strlen(reversedString);
        char* myString = malloc(1000);

        for(i = length; i >= 0; i--){
                strncat(myString, &reversedString[i],1);
        }
        return myString;
}

void int_to_string(int value, int base){

        char* result = malloc(1000); //NEEDS TO BE FREED?
        int remainder;
        while(value != 0){
                remainder = value % base;

                if(remainder == 10 && base == 16){
                        value /= base;
                        char myChar = 'A';
                        strncat(result, &myChar, 1);
                }
                else if(remainder == 11 && base == 16){
                                        value /= base;
                                        char myChar = 'B';
                                        strncat(result, &myChar, 1);
                                }
                else if(remainder == 12 && base == 16){
                                        value /= base;
                                        char myChar = 'C';
                                        strncat(result, &myChar, 1);
                                }
                else if(remainder == 13 && base == 16){
                                        value /= base;
                                        char myChar = 'D';
                                        strncat(result, &myChar, 1);
                                }
                else if(remainder == 14 && base == 16){
                                        value /= base;
                                        char myChar = 'E';
                                        strncat(result, &myChar, 1);
                                }
                else if(remainder == 15 && base == 16){
                                        value /= base;
                                        char myChar = 'F';
                                        strncat(result, &myChar, 1);
                                }
                else{
                        value /= base;
                        char myChar = remainder += '0';
                        strncat(result, &myChar, 1);
                }
        }
        if(base == 16){
                printf("0x");
                if(strlen(result) < 8){
                        for(size_t i = 8; i > strlen(result); i--){
                                printf("0");
                        }
                }
                printf("%s\n",reverseString(result));
        }
        if(base == 2){
                printf("0b");
                if(strlen(result) < 32){
                        for(size_t i = 32; i > strlen(result); i--){
                                printf("0");
                        }
                }
                printf("%s\n",reverseString(result));
        }
        if(base == 10){
                printf("%s\n",reverseString(result));
           }
}

// Parse operands, which are defined in the EBNF to be
// integer literals or unary minus or expressions
struct parse_node_st * parse_operand(struct parse_table_st *pt,
                                     struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np1;

    if (scan_table_accept(st, TK_MINUS)) {
                tp = scan_table_get(st, -1);
                np1 = parse_node_new(pt);
                np1->type = EX_OPER1;
                np1->oper1.oper = OP_MINUS;
                np1->oper1.operand = parse_operand(pt, st);
        }
        else if (scan_table_accept(st, TK_NOT)) {
                tp = scan_table_get(st, -1);
                np1 = parse_node_new(pt);
                np1->type = EX_OPER1;
                np1->oper1.oper = OP_NOT;
                np1->oper1.operand = parse_operand(pt, st);
        }
        else if (scan_table_accept(st, TK_BINLIT)) {
                                tp = scan_table_get(st, -1);
                np1 = parse_node_new(pt);
                        np1->type = EX_INTVAL;
                        np1 -> intval.value = string_to_int(tp->name, 2);
        }
        else if (scan_table_accept(st, TK_HEXLIT)) {
                tp = scan_table_get(st, -1);
                np1 = parse_node_new(pt);
                np1->type = EX_INTVAL;
                np1 -> intval.value = string_to_int(tp->name, 16);

         }
        else if (scan_table_accept(st, TK_INTLIT)) {
                tp = scan_table_get(st, -1);
                np1 = parse_node_new(pt);
                np1->type = EX_INTVAL;
                np1 -> intval.value = string_to_int(tp->name, 10);

    }
        else if(scan_table_accept(st, TK_LPAREN)){
                        tp = scan_table_get(st, -1);
                np1 = parse_expression(pt, st);
                if(!scan_table_accept(st, TK_RPAREN)){
                parse_error("Expecting Right");
                }
        }
    else {
        parse_error("Bad operand");
    }

    return np1;
  }

int evaluate(struct parse_node_st *np){
        if(np->type == EX_INTVAL){
                return np->intval.value;
        }
        else if(np->type == EX_OPER2){
                int leftOP = evaluate(np->oper2.left);
                int rightOP = evaluate(np->oper2.right);

                if(np->oper2.oper == OP_PLUS){
                        return leftOP + rightOP;
                }
                else if(np->oper2.oper == OP_MINUS){
                        return leftOP - rightOP;
                }
                else if(np->oper2.oper == OP_MULT){
                        return leftOP * rightOP;
                }
                else if(np->oper2.oper == OP_DIV){
                        return leftOP / rightOP;
                }
                else if(np->oper2.oper == OP_XOR){
                        return leftOP ^  rightOP;
                }
                else if(np->oper2.oper == OP_OR){
                        return leftOP | rightOP;
                }
                else if(np->oper2.oper == OP_AND){
                        return leftOP & rightOP;
                }
                else if(np->oper2.oper == OP_RSR){
                        return leftOP >> rightOP;
                }
                else if(np->oper2.oper == OP_LSL){
                        return leftOP << rightOP;
                }

        }
        else if(np->type == EX_OPER1){
                int oper = evaluate(np->oper1.operand);
                if(np->oper1.oper == OP_MINUS){
                        oper *= -1;
                }
                else if(np->oper1.oper == OP_NOT){
                        oper = ~oper;
                }
        }
}
