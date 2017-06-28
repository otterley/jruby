package org.jruby.java.invokers;

import java.lang.reflect.Field;

import org.jruby.RubyModule;
import org.jruby.javasupport.JavaUtil;
import org.jruby.runtime.ThreadContext;
import org.jruby.runtime.builtin.IRubyObject;

public class StaticFieldGetter extends FieldMethodZero {

    public StaticFieldGetter(String name, RubyModule host, Field field) {
        super(name, host, field);
    }

    @Override
    public final IRubyObject call(ThreadContext context, IRubyObject self, RubyModule clazz, String name) {
        try {
            return JavaUtil.convertJavaToUsableRubyObject(context.runtime, field.get(null));
        }
        catch (IllegalAccessException ex) { return handleGetException(context.runtime, ex); }
    }

}
