#include <emacs-module.h>
int plugin_is_GPL_compatible;

#include <stdlib.h>
#include <string.h>
#include <time.h>

static char *
extract_utf8_string (emacs_env *env, emacs_value lisp_str)
{
  ptrdiff_t size = 0;
  char * buf = NULL;

  env->copy_string_contents (env, lisp_str, buf, &size);
  buf = malloc (size);
  env->copy_string_contents (env, lisp_str, buf, &size);
  return buf;
}

static emacs_value
strptime_core (emacs_env *env, ptrdiff_t nargs, emacs_value *args,
               void *data)
{
  char * s1 = NULL;
  char * s2 = NULL;

  s1 = extract_utf8_string (env, args[0]);
  s2 = extract_utf8_string (env, args[1]);

  struct tm tm;

  memset(&tm, 0, sizeof tm);
  if (strptime(s1, s2, &tm) == NULL) {
    static const char message[] = "STRING and FORMAT not match";
    emacs_value error_args[] = {
      env->make_string (env, message, strlen (message)),
      args[0],
      args[1],
    };
    env->non_local_exit_signal
      (env, env->intern (env, "error"),
       env->funcall (env, env->intern (env, "list"), 3, error_args));    
  }

  free (s1);
  free (s2);

  emacs_value list_args[] = {
    env->make_integer (env, tm.tm_sec),
    env->make_integer (env, tm.tm_min),
    env->make_integer (env, tm.tm_hour),
    env->make_integer (env, tm.tm_mday),
    env->make_integer (env, tm.tm_mon + 1),
    env->make_integer (env, tm.tm_year + 1900),
    env->make_integer (env, tm.tm_wday),
    tm.tm_isdst ? env->intern (env, "t") : env->intern (env, "nil"),
    env->make_integer (env, tm.tm_gmtoff),
  };

  return env->funcall (env, env->intern (env, "list"), 9, list_args);
}

/* Provide FEATURE to Emacs.  */
static void
provide (emacs_env *env, const char *feature)
{
  emacs_value Qfeat = env->intern (env, feature);
  emacs_value Qprovide = env->intern (env, "provide");
  emacs_value args[] = { Qfeat };

  env->funcall (env, Qprovide, 1, args);
}

int
emacs_module_init(struct emacs_runtime *runtime)
{
  emacs_env *env = runtime->get_environment (runtime);
  emacs_value func = env->make_function
    (env, 2, 2, strptime_core,
     "Parse the time in STRING according to FORMAT.\n"
     "Return (SEC MINUTE HOUR DAY MONTH YEAR DOW DST UTCOFF).\n\n"
     "(fn string format)",
     NULL);
  emacs_value symbol = env->intern (env, "strptime-core");
  emacs_value args[] = {symbol, func};
  env->funcall (env, env->intern (env, "defalias"), 2, args);

  provide (env, "strptime-core");
  return 0;
}
