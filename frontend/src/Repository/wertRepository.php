<?php

namespace App\Repository;

use App\Entity\Module;
use App\Entity\Wert;
use DateTime;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

class wertRepository extends ServiceEntityRepository
{

    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, Wert::class);
    }

    public function getWerteByPeriodAndModule(DateTime $begin, DateTime $end, Module $module){
            $qb = $this->createQueryBuilder('w');
            return $qb ->select('w')
                ->where($qb->expr()->between('w.zeit', ':begin', ':end'))
                ->andWhere('w.modul = :module')
                ->setParameter('begin', $begin)
                ->setParameter('end', $end)
                ->setParameter('module', $module)
                ->getQuery()
                ->getResult();

    }
}