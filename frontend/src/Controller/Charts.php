<?php

namespace App\Controller;

use App\Exception\InputValidationException;
use App\Repository\ModuleRepository;
use App\Repository\PlatformRepository;
use App\Repository\TypRepository;
use App\Repository\wertRepository;
use App\Service\InputValidator;
use DateTime;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

class Charts extends AbstractController
{
    private $WertRepository;
    private $PlatformRepository;
    private $ModuleRepository;
    private $TypRepository;

    public function __construct( wertRepository $WertRepository,
    PlatformRepository $PlatformRepository,
    ModuleRepository $ModuleRepository,
    TypRepository $TypRepository)
    {
        $this->WertRepository = $WertRepository;
        $this->PlatformRepository = $PlatformRepository;
        $this->ModuleRepository = $ModuleRepository;
        $this->TypRepository = $TypRepository;
    }

    /**
     * @Route("/", methods={"GET"})
     */
    public function rootAction(): response
    {
        return $this->redirectToRoute('charts');
    }

    /**
     * @Route("/charts", methods={"GET"}, name="charts")
     */
    public function getChartsAction():Response
    {
        return $this->render('charts/charts.html.twig', [
        ]);
    }

    /**
     * @Route("/charts", methods={"POST"})
     * @param Request $request
     * @param InputValidator $inputValidator
     * @return JsonResponse
     */
    public function getWerte(Request $request, InputValidator $inputValidator):JsonResponse{
        try{
            $getDataDTO = $inputValidator->validateDataRequest($request);
        }catch (InputValidationException $e){
            return new JsonResponse(['status' => 'error', 'errors' => $e->getValidationErrors()], 400);
        }

        return new JsonResponse([   'status' => 'success',
                                    'werte' => $this->getWerteFromTheLastOneWeek($getDataDTO->getBegin(),
                                    $getDataDTO->getEnd())
        ]);
    }

    private function getWerteFromTheLastOneWeek(DateTime $begin, DateTime $end) : array{

        $werte = [];

        $types = $this->TypRepository->findAll();

        $counter = 0;

        foreach ($types AS $type){
            $counter2 = 0;
            $werte [$counter] ["Typ"] = $type->getBezeichnung();
            $modules = $this->ModuleRepository->findBy(['typ' => $type]);
            foreach($modules AS $module){
                $werte [$counter] ["platform"] [$counter2] ["name"] = $module->getPl()->getName();
                $werte [$counter] ["platform"] [$counter2] ["color"] = $module->getPl()->getFarbe();
                $datas = $this->WertRepository->getWerteByPeriodAndModule($begin, $end, $module);
                $counter3 = 0;
                $average = 0;
                foreach($datas AS $data){
                    $werte [$counter] ["platform"] [$counter2] ["data"] [$counter3] ['x']=   $data->getZeit()->format('d/m/Y/H:i');

                    $werte [$counter] ["platform"] [$counter2] ["data"] [$counter3] ['y']=   $data->getWert();
                    $average += $data->getWert();
                    $counter3++;
                }
                if($counter3 !== 0){
                    $werte [$counter] ["platform"] [$counter2] ["average"] = round($average / $counter3, 2);
                }

                $counter2++;
            }
            $counter++;
        }
        return $werte;
    }


}