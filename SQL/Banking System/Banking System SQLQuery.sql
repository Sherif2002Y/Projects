create database Bank_sys;

create table BANK (
   NAME                 varchar(20)          not null,
   ADDRESS              varchar(20)           not null,
   CODE                 numeric(15)           not null,
   constraint PK_BANK primary key (CODE)
)

create table Branch (
   Code                numeric(15)           not null,
   branch_num            numeric(15)           not null,
   ADDRESS              varchar(20)           not null,
   constraint PK_BRANCH primary key  (branch_num ),
   constraint fk_bank_branch foreign key(Code) references BANK(CODE)
)

create table Customer (
   branch_num            numeric(15)           not null,
   SSN                  numeric(20)          not null,
   NAME                 varchar(20)          not null,
   PHONE                numeric(11)   unique      null,
   ADDRESS              varchar(20)           null,
   constraint PK_Customer primary key  (SSN)
)

alter table Customer
   add constraint FK_COSTOMER_HAS1_BRANCH foreign key (branch_num)
      references BRANCH (branch_num)
create table EMPLOYEES (
   PHONE                numeric(11)    unique      null,
   NAME                 varchar(20)          not null,
   ADDRESS              varchar(20)           not null,
   EMPLOEE_ID           numeric(8)           not null,
   constraint PK_EMPLOYEES primary key (EMPLOEE_ID),
)

create table IT_CONTANS (
   branch_num             numeric(15)           not null,
   EMPLOEE_ID           numeric(8)           not null,
   constraint PK_IT_CONTANS primary key ( branch_num , EMPLOEE_ID),
   constraint FK_IT_CONTA_IT_CONTAN_BRANCH foreign key ( branch_num )
      references Branch ( branch_num ),
	constraint FK_IT_CONTA_IT_CONTAN_EMPLOYEE foreign key (EMPLOEE_ID)
      references EMPLOYEES (EMPLOEE_ID)
)


create table ACCOUNT (
   SSN                  numeric(20)          not null,
   ACCOUNT_NUM          numeric(20)          not null,
   ACCOUNT_TYPE         varchar(8)           not null,
   BALANCE              numeric(15)          not null,
   constraint PK_ACCOUNT primary key  ( ACCOUNT_NUM),
   constraint FK_ACCOUNT_HAS_COSTOMER foreign key ( SSN)
      references Customer ( SSN)
)

create table LOAN (
   branch_num            numeric(15)           not null,
   LOAN_CODE            numeric(8)           not null,
   LOAN_TYPE            varchar(20)          not null,
   LOAN_NUMBER          numeric(15)          not null,
   LOAN_AMOUNT          numeric(15)          not null,
   ACCOUNT_NUM          numeric(20)          not null,
   constraint PK_LOAN primary key  ( LOAN_CODE),
   constraint FK_LOAN_BORROWER_ACCOUNT foreign key (ACCOUNT_NUM) references ACCOUNT (ACCOUNT_NUM),
	  constraint FK_LOAN_OFFERS_BRANCH foreign key (branch_num) references BRANCH (branch_num)
)
alter table loan
add EMPLOEE_ID numeric(8) ;
alter table loan
add constraint FK_LOAN_employee foreign key (EMPLOEE_ID) references employees (EMPLOEE_ID);

/*A*/
Select *
from  Branch
where branch_num not in(select branch_num from Customer );

/*B*/
Select *
from  Branch
where branch_num not in(select branch_num from IT_CONTANS);

/*C*/
select  top 1 with ties count(EMPLOYEES.EMPLOEE_ID) as 'loan added' ,EMPLOYEES.EMPLOEE_ID,EMPLOYEES.NAME  , EMPLOYEES.PHONE,EMPLOYEES.ADDRESS
from EMPLOYEES , LOAN 
where EMPLOYEES.EMPLOEE_ID = LOAN.EMPLOEE_ID
group by EMPLOYEES.EMPLOEE_ID,EMPLOYEES.NAME  , EMPLOYEES.PHONE,EMPLOYEES.ADDRESS
order by count(EMPLOYEES.EMPLOEE_ID) desc;

/*D*/
select top 1 with ties count(Customer.SSN) as 'number of loan' ,Customer.NAME,Customer.SSN,Customer.ADDRESS,Customer.PHONE
from Customer , ACCOUNT , LOAN
where Customer.SSN = ACCOUNT.SSN AND LOAN.ACCOUNT_NUM = ACCOUNT.ACCOUNT_NUM 
group by Customer.NAME,Customer.SSN,Customer.ADDRESS,Customer.PHONE
order by count(Customer.SSN) desc;

/*E*/
select distinct(Customer.SSN),Customer.NAME,Customer.ADDRESS,Customer.PHONE
from Customer , ACCOUNT , LOAN
where Customer.SSN not in (select ACCOUNT.SSN from ACCOUNT) or
(Customer.SSN = ACCOUNT.SSN  and ACCOUNT.ACCOUNT_NUM not in (select ACCOUNT_NUM from LOAN));

/*F*/
select count(loan.EMPLOEE_ID) as 'number of employees', Customer.SSN,Customer.NAME,Customer.ADDRESS,Customer.PHONE
from Customer left join ACCOUNT
on Customer.SSN = ACCOUNT.SSN left join LOAN
on LOAN.ACCOUNT_NUM = ACCOUNT.ACCOUNT_NUM 
group by Customer.SSN,Customer.NAME,Customer.ADDRESS,Customer.PHONE;
/*test*/
select LOAN.LOAN_NUMBER ,LOAN.LOAN_TYPE, LOAN.LOAN_AMOUNT ,Customer.NAME,EMPLOYEES.NAME
from Customer INNER join ACCOUNT
on Customer.SSN = ACCOUNT.SSN inner join LOAN
on LOAN.ACCOUNT_NUM = ACCOUNT.ACCOUNT_NUM inner join EMPLOYEES
on LOAN.EMPLOEE_ID =EMPLOYEES.EMPLOEE_ID;
