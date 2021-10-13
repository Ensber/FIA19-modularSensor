<?php

namespace App\Repository;

use App\Entity\Platform;
use DateTime;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

class PlatformRepository extends ServiceEntityRepository
{

    private ManagerRegistry $doctrine;

    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, Platform::class);
        $this->doctrine = $registry;
    }

    public function editPlatform(
        Platform $editPlatform,
        string $name,
        string $farbe,
        DateTime $abfrageinterval
    ){
        $platform = $editPlatform;
        $platform->setName($name);
        $platform->setFarbe($farbe);
        $platform->setAbfrageinterval($abfrageinterval);

        $manager = $this->doctrine->getManager();
        $manager->persist($platform);
        $manager->flush();
    }
}