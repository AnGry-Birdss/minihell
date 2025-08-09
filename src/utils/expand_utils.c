
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/expand_utils.h"
#include "../../include/minishell.h"

// Expand $VAR and $? in s, except inside single quotes
char *expand_vars_in_string(const char *s, char **env, int last_status)
{
	if (!s)
		return strdup("");
	char *out = malloc(strlen(s) * 4 + 1);
	if (!out) return NULL;
	int i = 0, j = 0;
	while (s[i]) {
		if (s[i] == '\'') {
			i++;
			while (s[i] && s[i] != '\'')
				out[j++] = s[i++];
			if (s[i] == '\'')
				i++;
			continue;
		}
		if (s[i] == '"') {
			i++;
			while (s[i] && s[i] != '"') {
				if (s[i] == '$') {
					i++;
					if (s[i] == '?') {
						j += sprintf(out + j, "%d", last_status);
						i++;
					} else if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == '_') {
						int k = 0;
						char var[128];
						while ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
							var[k++] = s[i++];
						var[k] = 0;
						char *val = get_env_value(env, var);
						if (val) j += sprintf(out + j, "%s", val);
					} else {
						out[j++] = '$';
					}
				} else {
					out[j++] = s[i++];
				}
			}
			if (s[i] == '"')
				i++;
			continue;
		}
		if (s[i] == '$') {
			i++;
			if (s[i] == '?') {
				j += sprintf(out + j, "%d", last_status);
				i++;
			} else if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == '_') {
				int k = 0;
				char var[128];
				while ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
					var[k++] = s[i++];
				var[k] = 0;
				char *val = get_env_value(env, var);
				if (val) j += sprintf(out + j, "%s", val);
			} else {
				out[j++] = '$';
			}
			continue;
		}
		out[j++] = s[i++];
	}
	out[j] = 0;
	return out;
}
