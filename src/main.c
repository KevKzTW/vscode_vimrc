#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include <err.h>

bool raw_command_to_json(struct json_object *element, char *src_str)
{
    int length = strlen(src_str);
    for (int k = 0; k < length; k++)
    {
        if (src_str[k] == '<')
        {
            char temp2[8];
            for (int ll = 0; ll < 7; ll++)
            {
                char current_char = src_str[k];
                temp2[ll] = current_char;
                k++;
                if (current_char == '>')
                {
                    temp2[ll + 1] = '\0';
                    break;
                }
            }

            json_object_array_add(element, json_object_new_string(temp2));
        }
        else if (src_str[k] == ':')
        {
            return false;
        }
        else if (src_str[k] == '\r')
        {
            ; //ignore
        }
        else
        {

            char temp[1];
            sprintf(temp, "%c", src_str[k]);
            json_object_array_add(element, json_object_new_string(temp));
        }
    }
    return true;
}

int main(int argc, char *argv)
{
    FILE *fp = fopen("../vimrc", "r");
    if (!fp)
    {
        fprintf(stderr, "%s\n", strerror(err));
        exit(-1);
    }
    char line[1024];
    char ch = getc(fp);
    int index = 0;
    int line_num = 0;

    struct json_object *imap_array = json_object_new_array();
    struct json_object *nmap_array = json_object_new_array();
    while (ch != EOF)
    {
        if (ch != '\n')
        {
            line[index++] = ch;
        }
        else
        {
            line[index] = '\0';
            index = 0;
            // printf("%s\n", line);
            char *delim = " ";
            char *pch = strtok(line, delim);
            char line_array[6][255] = {0};
            int j = 0;
            while (pch != NULL)
            {
                strcpy(line_array[j], pch);
                line_array[j][strlen(pch)] = '\0';
                j++;
                pch = strtok(NULL, delim);
            }

            if (strcmp("imap", line_array[0]) == 0 || strcmp(":imap", line_array[0]) == 0)
            {
                // printf("imap\n");
                struct json_object *before_element = json_object_new_array();
                raw_command_to_json(before_element, line_array[1]);

                struct json_object *after_element = json_object_new_array();
                bool is_legal = raw_command_to_json(after_element, line_array[2]);

                if (!is_legal)
                {
                    json_object_put(before_element);
                    json_object_put(after_element);
                }
                else
                {
                    struct json_object *element = json_object_new_object();
                    json_object_object_add(element, "before", before_element);
                    json_object_object_add(element, "after", after_element);
                    json_object_array_add(imap_array, element);
                }
            }
            else if (strcmp("map", line_array[0]) == 0 || strcmp("nmap", line_array[0]) == 0 || strcmp(":nmap", line_array[0]) == 0 || strcmp(":map", line_array[0]) == 0)
            {
                // printf("nmap\n");
                struct json_object *before_element = json_object_new_array();
                raw_command_to_json(before_element, line_array[1]);

                struct json_object *after_element = json_object_new_array();
                bool is_legal = raw_command_to_json(after_element, line_array[2]);

                if (!is_legal)
                {
                    json_object_put(before_element);
                    json_object_put(after_element);
                }
                else
                {
                    struct json_object *element = json_object_new_object();
                    json_object_object_add(element, "before", before_element);
                    json_object_object_add(element, "after", after_element);
                    json_object_array_add(nmap_array, element);
                }
            }
            else
            {
                printf("ignore %s\n", line_array[0]);
            }
        }
        ch = getc(fp);
    }
    struct json_object *root = json_object_new_object();
    json_object_object_add(root, "vim.insertModeKeyBindings", imap_array);
    json_object_object_add(root, "vim.normalModeKeyBindings", nmap_array);
    json_object_to_file("../setting.json", root);
    //printf("%s\n", json_object_to_json_string(root));
    json_object_put(root);
    fclose(fp);
    return 0;
}