//
//  CYYSubsectionTableViewDataSource.h
//  TableViewWithSubsections
//
//  Created by Joshua McKinnon on 19/11/12.
//  Copyright (c) 2012 Corduroy Enterprises. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "NSIndexPath+TableViewWithSubSections.h"
typedef enum {
	CYSubSectionIndexPathGroup,
	CYSubSectionIndexPathSubgroup,
	CYSubSectionIndexPathRow
}CYSubSectionIndexPath;

#import <Foundation/Foundation.h>

#pragma mark - NSIndexPath+TableViewWithSubSections Category -
@interface NSIndexPath (TableViewWithSubSections)

+ (NSIndexPath *)indexPathForRow:(NSUInteger)row inSubgroup:(NSUInteger)subgroup inGroup:(NSUInteger)group;
+ (NSIndexPath *)indexPathForSubgroup:(NSUInteger)subgroup inGroup:(NSUInteger)group;
@property(nonatomic,readonly) NSUInteger group;
@property(nonatomic,readonly) NSUInteger subgroup;
@property(nonatomic,readonly) NSUInteger subgroupRow;

@end

@protocol CYYSubsectionTableViewProxyDataSource;
/**
 Create a tableView that has Sections, Subsections and Rows. Or rather, to avoid confusing nomenclature,
 Groups, Subgroups and Rows.
 Groups and Subgroups should appear as tableView sections; Rows map to tableView Rows.
 
 We do not currently implement the tableView data source methods that support editing of rows.
 */
@interface CYYSubsectionTableViewDataSource : NSObject <UITableViewDataSource, UITableViewDelegate>

@property (strong, nonatomic) id<CYYSubsectionTableViewProxyDataSource> dataSource;
@property (strong, nonatomic) UITableView *tableView;

#pragma mark - Table view data source
- (NSUInteger)numberOfSectionsInTableView:(UITableView *)tableView;
- (NSUInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSUInteger)section;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;
////- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section;

#pragma mark - Table view delegate
- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSUInteger)section;
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSUInteger)section;
////- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
////- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section;
////- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section;
#pragma mark - Intermediaries
/** tableView's sectionIndex for this group 
 This method must take into account the number of groups _and_ subgroups that preceed it in the tableView.
 
 @returns The tableView section index for this group.
 @param group The index of the group
 */
- (NSUInteger)sectionIndexForGroup:(NSUInteger)group;
/** tableView's section index for this subgroup.
 @returns The tableView section index for the given subgroup 
 @param subgroup The index of the subgroup 
 @param group The index of the group containing this subgroup */
- (NSUInteger)sectionIndexForSubgroup:(NSUInteger)subgroup inGroup:(NSUInteger)group;

- (NSIndexPath *)groupAndSubgroupForSection:(NSUInteger)section;
@end

#pragma mark - Proxy Table View Data Source -
@protocol CYYSubsectionTableViewProxyDataSource <NSObject>
@required
/** Asks the data source to return the number of Groups in the tableView
 @param tableView The table view requesting this information.
 @return The number of groups in tableView*/
-(NSUInteger)numberOfGroupsInTableView:(UITableView *)tableView;
/** Ask the data source to return the number of Subgroups in the given group
 @param group An index number identifying the Group in the table view
 @param tableView The table view requesting this information.
 @return The number of groups in the table view.*/
-(NSUInteger)tableView:(UITableView *)tableview numberOfSubgroupsInGroup:(NSUInteger)group;
/** Asks the data source to return the number of rows in the given subgroup of the given group.
 @param subgroup An index number identifying the subgroup.
 @param group An index number identifying the group
 @param tableView The table view requesting this information.
 @return The number of rows in the given subgroup of the given group
 */
-(NSUInteger)tableView:(UITableView *)tableview numberOfRowsInSubgroup:(NSUInteger)subgroup ofGroup:(NSUInteger)group;
/** Asks the data source for a tableViewCell for the row identified by a three-component index path
 
 Don't forget to look at NSIndexPath+TableViewWithSubSections.h for easy three-component index paths.
 
 @param indexPath A three-component index path (Group, Subgroup, Row) identifying the row.
 @param tableView The table view requesting the cell.
 @return A table view cell.
 */
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtThreeComponentIndexPath:(NSIndexPath *)indexPath;
@optional
/** Asks the data source to provide a custom header view
 
 @param indexPath An index path specifying the group and subgroup for this header 
 @param tableView The tableView requesting the header view 
 @return a header view */
-(UIView *)tableView:(UITableView *)tableView headerForSubGroupAtIndexPath:(NSIndexPath *)indexPath;

/** Asks the <strike>delegate</strike> data source for the height to use for the header of the given subgroup
 
 @param indexPath An index path specifying the group and subgroup for this header
 @param tableView The tableView requesting the header view
 @return A floating-point value that specifies the height (in points) of the header for the group or subgroup.
 */
-(CGFloat)tableView:(UITableView *)tableView heightForHeaderForSubgroupAtIndexPath:(NSIndexPath *)indexPath;
/** Asks the data source for the title of the header for the group or subgroup at the given index path
 
 @param indexPath An index path specifying the group and subgroup for this header
 @param tableView The tableView requesting the header view
 @return A string or nil if you'd like no title. 
 */
- (NSString *)tableView:(UITableView *)tableView titleForHeaderForSubgroupAtIndexPath:(NSIndexPath *)indexPath;
@end
