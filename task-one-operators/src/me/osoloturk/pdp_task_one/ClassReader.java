package me.osoloturk.pdp_task_one;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static me.osoloturk.pdp_task_one.Constants.OPERATOR_GROUPS;

public class ClassReader {
    private ArrayList<String> reads;
    private ArrayList<OperatorGroup> groups;

    public ClassReader(){
        reads = new ArrayList();
        groups = (ArrayList<OperatorGroup>) OPERATOR_GROUPS.clone();
    }

    public void addDetection(final String value) {
        reads.add(value);
        for(OperatorGroup group : groups) {
            if(group.contains(value)) {
                group.incr_count();
            }
        }
    }

    public List<String> getCategories(final String value) {
        List<String> response = new ArrayList<>();
        for(OperatorGroup group : groups) {
            if(group.contains(value)) {
                response.add(group.getGroupName());
            }
        }
        return response;
    }

    public List<OperatorGroup> getGroups(){
        return groups;
    }

}
