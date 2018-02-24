
#ifndef RUNNING_MEDIAN_MAX_SIZE
#define RUNNING_MEDIAN_MAX_SIZE 11
#endif


static void rm_insertion_sort(int arr[], int length) {
		
	for (int i = 0; i < length; i++) {
		int j = i;
		
        while (j > 0 && arr[j] < arr[j-1]) {
            int temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            j--;
        }
    }
}

/* microflo_component yaml
name: RunningMedian
description: Calculate a running median of latest values
inports:
  in:
    type: integer
    description: "Insert a new value and update median"
    triggering: true
  reset:
    type: bang
    description: "Clear existing values"
  values:
    type: integer
    description: Number of values to use. Maximum is limited by RUNNING_MEDIAN_MAX_SIZE, set at compile time
    default: 11
outports:
  out:
    type: integer
    description: ""
microflo_component */
class RunningMedian : public SingleOutputComponent {

private:
    int values[RUNNING_MEDIAN_MAX_SIZE];
    int valid_values;
    int max_values;
    int insert_at;

public:
    RunningMedian()
        : valid_values(0)
        , max_values(RUNNING_MEDIAN_MAX_SIZE)
        , insert_at(0)

    {
    }

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace RunningMedianPorts;

        if (port == InPorts::reset) {
            valid_values = 0;
            insert_at = 0;
        } else if (port == InPorts::values) {
            const int m = in.asInteger();
            if (m < RUNNING_MEDIAN_MAX_SIZE) {
                max_values = m;
            } else {
                max_values = RUNNING_MEDIAN_MAX_SIZE;
            }
        } else if (port == InPorts::in) {
            if (in.isInteger()) {
                insert(in.asInteger());
            }
            if (valid_values) {
                send((long)calculateMedian(), OutPorts::out);
            } else {
                send(Packet(), OutPorts::out);
            }
        }
    }

private:
    void insert(int new_value) {
        if (insert_at >= max_values) {
            insert_at = 0;
        }
        if (insert_at >= valid_values) {
            valid_values = insert_at+1;
        }
        values[insert_at] = new_value;
        insert_at += 1;
    }
    
    int calculateMedian() {
        int sorted[RUNNING_MEDIAN_MAX_SIZE];
        for (int i=0; i<valid_values; i++) {
            sorted[i] = values[i];
        }
        rm_insertion_sort(sorted, valid_values);

        if (valid_values % 2) {
            return sorted[valid_values/2];
        } else {
            const int lower = sorted[(valid_values/2)-1];
            const int higher = sorted[(valid_values/2)];
            return (higher+lower)/2;
        }
    }
};


