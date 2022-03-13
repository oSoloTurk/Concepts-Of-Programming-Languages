package me.osoloturk.pdp_task_one;

import java.util.List;

public class OperatorGroup {

    private final List<String> operators;
    private final String groupName;
    private int count;

    public OperatorGroup(List<String> operators, String groupName) {
        this.operators = operators;
        this.groupName = groupName;
        this.count = 0;
    }

    public String getGroupName() {
        return groupName;
    }

    public void incr_count(){
        count++;
    }

    public boolean contains(final String value) {
        return operators.contains(value);
    }

    public final int getCount() {
        return count;
    }
    @Override
    public String toString() {
        return groupName + ":" + count;
    }
    @Override
    public OperatorGroup clone(){
        return new OperatorGroup(operators, groupName);
    }
}
