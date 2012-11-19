//
//  CYYSubsectionTableViewDataSource.m
//  TableViewWithSubsections
//
//  Created by Joshua McKinnon on 19/11/12.
//  Copyright (c) 2012 Corduroy Enterprises. All rights reserved.
//

#import "CYYSubsectionTableViewDataSource.h"


@implementation CYYSubsectionTableViewDataSource

#pragma mark - Table view data source

- (NSUInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	NSUInteger numberOfSections = 0;
	for (NSUInteger groupIndex=0; groupIndex < [self.dataSource numberOfGroupsInTableView:self.tableView]; groupIndex++) {
		NSUInteger numberOfSubgroupsInGroup = [self.dataSource tableView:self.tableView numberOfSubgroupsInGroup:groupIndex];
		if (numberOfSubgroupsInGroup >0) {
			numberOfSections += numberOfSubgroupsInGroup;
			numberOfSections += 1; //Add one for the *group*'s section
		}
	}
	return numberOfSections;
}

- (NSUInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSUInteger)section
{
	NSIndexPath *groupAndSubgroup = [self groupAndSubgroupForSection:section];
	return [self.dataSource tableView:self.tableView
			   numberOfRowsInSubgroup:[groupAndSubgroup indexAtPosition:1]
							  ofGroup:[groupAndSubgroup indexAtPosition:0]];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	NSIndexPath *groupAndSubgroup = [self groupAndSubgroupForSection:indexPath.section];
	NSIndexPath *threeComponentIndexPath = [NSIndexPath indexPathForRow:indexPath.row
															 inSubgroup:groupAndSubgroup.subgroup
																inGroup:groupAndSubgroup.group];
	UITableViewCell *cell = [self.dataSource tableView:self.tableView
				   cellForRowAtThreeComponentIndexPath:threeComponentIndexPath];
	return cell;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
	NSIndexPath *groupAndSubgroup = [self groupAndSubgroupForSection:section];
	return [self.dataSource tableView:self.tableView titleForHeaderForSubgroupAtIndexPath:groupAndSubgroup];
}
#pragma mark - Table view delegate

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSUInteger)section
{
	NSIndexPath *groupAndSubgroup = [self groupAndSubgroupForSection:section];
	UIView *headerView = [self.dataSource tableView:self.tableView headerForSubGroupAtIndexPath:groupAndSubgroup];
	return headerView;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSUInteger)section
{
	NSIndexPath *groupAndSubgroup = [self groupAndSubgroupForSection:section];
	CGFloat headerHeight = [self.dataSource tableView:self.tableView heightForHeaderForSubgroupAtIndexPath:groupAndSubgroup];
	return headerHeight;
}

#pragma mark - intermediaries
- (NSIndexPath *)groupAndSubgroupForSection:(NSUInteger)section
{
	NSUInteger cumulativesubgroupIndex =0;
	for (NSUInteger groupIndex = 0; groupIndex < [self.dataSource numberOfGroupsInTableView:self.tableView]; groupIndex++) {
		NSUInteger numberOfSubgroupsInGroup = [self.dataSource tableView:self.tableView numberOfSubgroupsInGroup:groupIndex];
		if (numberOfSubgroupsInGroup > 0) {
			cumulativesubgroupIndex ++;
			if (cumulativesubgroupIndex == section) {
				return [NSIndexPath indexPathForSubgroup:0 inGroup:groupIndex];
			}
			for (NSUInteger subgroupIndex =0 ; subgroupIndex < numberOfSubgroupsInGroup ; subgroupIndex++) {
				cumulativesubgroupIndex ++;
				if (cumulativesubgroupIndex == section) {
					return [NSIndexPath indexPathForSubgroup:subgroupIndex inGroup:groupIndex];
				}
			}
		}
	}
	return nil;
}
- (NSUInteger)sectionIndexForGroup:(NSUInteger)group
{
	NSUInteger sectionIndex = 0;
	for (int groupIndex =0; groupIndex < group; groupIndex++) {
		NSUInteger numberOfSubgroupsInGroup = [self.dataSource tableView:self.tableView numberOfSubgroupsInGroup:groupIndex];
		if (numberOfSubgroupsInGroup >0) {
			sectionIndex += numberOfSubgroupsInGroup;
			sectionIndex += 1; // Add one for the *group*'s section.
		}
	}
	return sectionIndex;
}

- (NSUInteger)sectionIndexForSubgroup:(NSUInteger)subgroup inGroup:(NSUInteger)group
{
	NSUInteger sectionIndexForGroup = [self sectionIndexForGroup:group];
	return sectionIndexForGroup + subgroup;
}

@end


#pragma mark - NSIndexPath Category -
@implementation NSIndexPath (TableViewWithSubSections)

+ (NSIndexPath *)indexPathForRow:(NSUInteger)row inSubgroup:(NSUInteger)subgroup inGroup:(NSUInteger)group
{
	NSUInteger indexes[] = {group, subgroup, row};
	return [NSIndexPath indexPathWithIndexes:indexes length:3];
}

+ (NSIndexPath *)indexPathForSubgroup:(NSUInteger)subgroup inGroup:(NSUInteger)group
{
	NSUInteger indexes[] = {group,subgroup};
	return [NSIndexPath indexPathWithIndexes:indexes length:2];
}
-(NSUInteger)group
{
	return [self indexAtPosition:CYSubSectionIndexPathGroup];
}

- (NSUInteger)subgroup
{
	return [self indexAtPosition:CYSubSectionIndexPathSubgroup];
}

- (NSUInteger)subgroupRow
{
	return [self indexAtPosition:CYSubSectionIndexPathRow];
}
@end
