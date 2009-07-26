trigger Task_AggregateTaskEffort on Task__c (before update) {
    List <TaskEffort__c> taskEffortList = [
        select Id, 
               Status__c,
               Task__c
          from TaskEffort__c 
         where Task__c in : Trigger.newMap.keySet ()
    ];
    
    // 
    // Reset the status, started on, completed on fields
    //
    
    for(Task__c task : Trigger.new) {
        task.StartedOn__c = null;
        task.CompletedOn__c = null;
    
        if (task.DueOn__c == null)
            task.Status__c = System.Label.StatusNotYetEstimated;
        else
            task.Status__c = System.Label.StatusNotYetStarted;
    }
    
    //
    // Increment new hours
    //
    
    for(TaskEffort__c taskEffort : taskEffortList) {
        if (Trigger.newMap.containsKey (taskEffort.Task__c) == false)
            continue;

        Task__c task = Trigger.newMap.get (taskEffort.Task__c);
        Boolean late = task.DueOn__c <= Date.Today ();
        
        if (task.Status__c == System.Label.StatusBlocked)
            continue;
        if (task.Status__c == System.Label.StatusInternalError)
            continue;
            
        if (taskEffort.Status__c == System.Label.StatusBlocked)
            task.Status__c = System.Label.StatusBlocked;
        else if (taskEffort.Status__c == System.Label.StatusCompleted && late == true)
            task.Status__c = System.Label.StatusCompletedLate;
        else if (taskEffort.Status__c == System.Label.StatusCompleted)
            task.Status__c = System.Label.StatusCompleted;
        else if (taskEffort.Status__c == System.Label.StatusInProgress && late == true)
            task.Status__c = System.Label.StatusInProgressLate;
        else if (taskEffort.Status__c == System.Label.StatusInProgress)
            task.Status__c = System.Label.StatusInProgress;
        else
            task.Status__c = System.Label.StatusInternalError;
            
            
        //
        // Update the started date
        //
        
        if (taskEffort.Status__c == System.Label.StatusInProgress) {
            if (task.StartedOn__c == null)
                task.StartedOn__c = Date.Today ();
            else if (task.StartedOn__c > Date.Today ())
                task.StartedOn__c = Date.Today ();
        }
        
        
        //
        // Update the completed date
        //
        
        if (taskEffort.Status__c == System.Label.StatusCompleted) {
            if (task.CompletedOn__c == null)
                task.CompletedOn__c = Date.Today ();
            else if (task.CompletedOn__c < Date.Today ())
                task.CompletedOn__c = Date.Today ();
        }
        
    }
}