package me.osoloturk.pdp_task_one;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.stream.Collectors;

public class Constants {

    public static final ArrayList<OperatorGroup> OPERATOR_GROUPS;

    public static final LinkedList<String> OPERATORS;

    static {
        OPERATOR_GROUPS = new DCOperatorGroups();
        OPERATORS = new LinkedList<>();
        OPERATOR_GROUPS.add(new OperatorGroup(Arrays.asList(
                "++", "--"
        ), "Tekli Operator"));
        OPERATOR_GROUPS.add(new OperatorGroup(Arrays.asList(
                "+", "-", "*", "/", "%",
                "&", "|", "^", "+=", "-=",
                "/=", "*=", "%=", "&=", "|=", "^=",
                "<", "<=", ">", ">=", "==", "!=",
                "&&", "||", "!"
        ), "Ikili Operator"));
        OPERATOR_GROUPS.add(new OperatorGroup(Arrays.asList(
                "+", "++", "-", "--", "*", "/", "%",
                "&", "|", "^", "=", "+=", "-=",
                "/=", "*=", "%=", "&=", "|=", "^="
        ), "Sayisal Operator"));
        OPERATOR_GROUPS.add(new OperatorGroup(Arrays.asList(
                "<", "<=", ">", ">=", "==", "!="
        ), "Iliskisel Operator"));
        OPERATOR_GROUPS.add(new OperatorGroup(Arrays.asList(
                "&&", "||", "!"
        ), "Mantiksal Operator"));
        OPERATORS.addFirst("+");
        OPERATORS.addFirst("-");
        OPERATORS.addFirst("*");
        OPERATORS.addFirst("/");
        OPERATORS.addFirst("%");
        OPERATORS.addFirst("&");
        OPERATORS.addFirst("|");
        OPERATORS.addFirst("^");
        OPERATORS.addFirst("=");
        OPERATORS.addFirst("<");
        OPERATORS.addFirst(">");
        OPERATORS.addFirst("!");
        OPERATORS.addFirst("--");
        OPERATORS.addFirst("++");
        OPERATORS.addFirst("+=");
        OPERATORS.addFirst("-=");
        OPERATORS.addFirst("<=");
        OPERATORS.addFirst("/=");
        OPERATORS.addFirst("*=");
        OPERATORS.addFirst("%=");
        OPERATORS.addFirst("&=");
        OPERATORS.addFirst("|=");
        OPERATORS.addFirst("^=");
        OPERATORS.addFirst(">=");
        OPERATORS.addFirst("==");
        OPERATORS.addFirst("!=");
        OPERATORS.addFirst("&&");
        OPERATORS.addFirst("||");
    }

    /*
        DeepCloneableOperatorGroups
     */
    public static class DCOperatorGroups extends ArrayList<OperatorGroup> {
        @Override
        public ArrayList<OperatorGroup> clone() {
            return (ArrayList<OperatorGroup>) this.stream().map(OperatorGroup::clone).collect(Collectors.toList());
        }
    }
}
