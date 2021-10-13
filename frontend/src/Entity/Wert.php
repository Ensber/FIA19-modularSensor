<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Wert
 *
 * @ORM\Table(name="Wert", indexes={@ORM\Index(name="Modul_ID", columns={"Modul_ID"})})
 * @ORM\Entity
 */
class Wert
{
    /**
     * @var int
     *
     * @ORM\Column(name="Wert_ID", type="integer", nullable=false, options={"unsigned"=true})
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="IDENTITY")
     */
    private $wertId;

    /**
     * @var \DateTime
     *
     * @ORM\Column(name="Zeit", type="datetime", nullable=false)
     */
    private $zeit;

    /**
     * @var float
     *
     * @ORM\Column(name="Wert", type="float", precision=10, scale=0, nullable=false)
     */
    private $wert;

    /**
     * @var Module
     *
     * @ORM\ManyToOne(targetEntity="Module")
     * @ORM\JoinColumns({
     *   @ORM\JoinColumn(name="Modul_ID", referencedColumnName="Modul_ID")
     * })
     */
    private $modul;

    /**
     * @return int
     */
    public function getWertId(): int
    {
        return $this->wertId;
    }

    /**
     * @param int $wertId
     */
    public function setWertId(int $wertId): void
    {
        $this->wertId = $wertId;
    }

    /**
     * @return \DateTime
     */
    public function getZeit(): \DateTime
    {
        return $this->zeit;
    }

    /**
     * @param \DateTime $zeit
     */
    public function setZeit(\DateTime $zeit): void
    {
        $this->zeit = $zeit;
    }

    /**
     * @return float
     */
    public function getWert(): float
    {
        return $this->wert;
    }

    /**
     * @param float $wert
     */
    public function setWert(float $wert): void
    {
        $this->wert = $wert;
    }

    /**
     * @return Module
     */
    public function getModul(): Module
    {
        return $this->modul;
    }

    /**
     * @param Module $modul
     */
    public function setModul(Module $modul): void
    {
        $this->modul = $modul;
    }


}
