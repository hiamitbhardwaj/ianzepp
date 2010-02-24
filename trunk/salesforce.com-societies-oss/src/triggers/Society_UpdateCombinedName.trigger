trigger Society_UpdateCombinedName on Society__c (before insert, before update) {
    for(Society__c society : Trigger.new) {
        society.CombinedName__c = society.Account__c + '::' + society.Name__c;
    }
}