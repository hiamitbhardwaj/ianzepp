/**
 * Societies Discussion Board (OSS)
 *
 * Copyright (C) 2009 - 2010, Ian Zepp <ian.zepp@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

trigger SocietyComment_SetScore on SocietyComment__c (before update) {
    for(SocietyComment__c societyComment : Trigger.new) {
        societyComment.Score__c  = 0;
        societyComment.Score__c += societyComment.Liked__c;
        societyComment.Score__c -= societyComment.Disliked__c;
        societyComment.Score__c += 0.5 * societyComment.Saved__c;
        societyComment.Score__c -= 0.5 * societyComment.Reported__c;
    }
}